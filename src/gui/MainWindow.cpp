#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    _solver = std::make_shared<Solver>(this);

    connect(ui->createPuzzlePushButton, &QPushButton::clicked, this, &MainWindow::on_CreatePuzzleButtonClicked);
    connect(ui->choosePuzzlePushButton, &QPushButton::clicked, this, &MainWindow::on_ChoosePuzzleButtonClicked);
    connect(ui->startPushButton, &QPushButton::clicked, this, &MainWindow::on_StartButtonClicked);
    connect(ui->initialStatePushButton, &QPushButton::clicked, this, &MainWindow::on_InitialStateButtonClicked);
    connect(ui->goalStatePushButton, &QPushButton::clicked, this, &MainWindow::on_GoalStateButtonClicked);
    connect(ui->backPushButton, &QPushButton::clicked, this, &MainWindow::on_BackButtonClicked);
    connect(ui->nextPushButton, &QPushButton::clicked, this, &MainWindow::on_NextButtonClicked);

    connect(this, &MainWindow::signal_PuzzleCreated, _solver.get(), &Solver::on_PuzzleCreated);
    connect(_solver.get(), &Solver::signal_PuzzleSolved, this, &MainWindow::on_PuzzleSolved);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_CreatePuzzleButtonClicked() {
    QProcess process;
    QString program = "python3";
    QStringList arguments;

    arguments << "npuzzle-gen.py" << QString::number(ui->puzzleSizeSpinBox->value());

    if (ui->puzzleStateComboBox->currentText() == "Solvable") {
        arguments << "--solvable";
    } else if (ui->puzzleStateComboBox->currentText() == "Unsolvable") {
        arguments << "--unsolvable";
    }

    if (ui->iterationsSpinBox->value() != 10000) {
        arguments << "--iterations" << QString::number(ui->iterationsSpinBox->value());
    }

    process.start(program, arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    if (!this->ParseOutput(output)) {
        this->ClearPuzzleLayout();
        this->DisplayMessagePuzzleLayout("Invalid puzzle format.");
        return;
    }
    this->DisplayPuzzle(_puzzle_vector);

    ui->startPushButton->setEnabled(true);
}

void MainWindow::on_ChoosePuzzleButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Choose a puzzle", "", "Fichiers texte (*.txt)");

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the selected file.");
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    if (!this->ParseOutput(fileContent)) {
        this->ClearPuzzleLayout();
        this->DisplayMessagePuzzleLayout("Invalid puzzle format.");
        return;
    }
    this->DisplayPuzzle(_puzzle_vector);

    ui->startPushButton->setEnabled(true);
}

bool MainWindow::ParseOutput(const QString &output) {
    if (!_parser.Parse(output))
        return false;
    
    _puzzle_size = _parser.getPuzzleSize();
    _puzzle_vector = _parser.getPuzzleVector();
    _is_solvable = _parser.isSolvable();
    
    return true;
}

void MainWindow::DisplayPuzzle(const QVector<int>& puzzle) {
    this->ClearPuzzleLayout();

    if (!_is_solvable) {
        this->DisplayMessagePuzzleLayout("The puzzle is unsolvable.");
        return;
    }

    for (int i = 0; i < _puzzle_size; ++i) {
        for (int j = 0; j < _puzzle_size; ++j) {
            int index = i * _puzzle_size + j;
            int value = puzzle[index];

            QPushButton *button = new QPushButton(value == 0 ? "" : QString::number(value), this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            if (value == 0)
                button->setVisible(false);
            ui->puzzleGridLayout->addWidget(button, i, j);
        }
    }

    ui->puzzleGridLayout->update();
}

void MainWindow::on_StartButtonClicked() {
    ui->startPushButton->setEnabled(false);
    ui->menuGroupBox->setEnabled(false);

    if (ui->algorithmComboBox->currentText() == "A*") {
        _solver->setAlgorithm(std::make_shared<AStar>());
    } else if (ui->algorithmComboBox->currentText() == "IDA*") {
        _solver->setAlgorithm(std::make_shared<IDAStar>());
    }

    emit signal_PuzzleCreated(_puzzle_vector, _puzzle_size, ui->heuristicComboBox->currentText());
}

void MainWindow::on_InitialStateButtonClicked() {
    _current_state_index = 0;
    this->DisplayPuzzle(_solved_puzzle.first());
}

void MainWindow::on_GoalStateButtonClicked() {
    _current_state_index = _solved_puzzle.size() - 1;
    this->DisplayPuzzle(_solved_puzzle.last());
}

void MainWindow::on_BackButtonClicked() {
    if (_current_state_index > 0) {
        --_current_state_index;
        this->DisplayPuzzle(_solved_puzzle[_current_state_index]);
    }
}

void MainWindow::on_NextButtonClicked() {
    if (_current_state_index < _solved_puzzle.size() - 1) {
        ++_current_state_index;
        this->DisplayPuzzle(_solved_puzzle[_current_state_index]);
    }
}

void MainWindow::on_PuzzleSolved(const QVector<QVector<int>>& solved_puzzle, qint64 elapsed_ms, qint64 states_tested, qint64 max_states_in_memory) {
    if (solved_puzzle.isEmpty() || solved_puzzle.last().size() != _puzzle_size * _puzzle_size) {
        QMessageBox::warning(this, "Erreur", "La solution du puzzle est invalide.");
        return;
    }
    _solved_puzzle = solved_puzzle;
    _current_state_index = _solved_puzzle.size() - 1;

    ui->menuGroupBox->setEnabled(true);
    ui->resultGroupBox->setEnabled(true);
    ui->timeToProcessValueLabel->setText(this->FormatElapsedTime(elapsed_ms));
    ui->numberOfIterationsLabel->setText(QString::number(solved_puzzle.size() - 1));
    ui->statesTestedValueLabel->setText(QString::number(states_tested));
    ui->complexityTimeValueLabel->setText(QString::number(max_states_in_memory));
    
    this->DisplayPuzzle(_solved_puzzle.last());
}

QString MainWindow::FormatElapsedTime(qint64 elapsed_ms) {
    qint64 seconds = elapsed_ms / 1000;
    qint64 minutes = seconds / 60;
    seconds %= 60;
    qint64 ms = elapsed_ms % 1000;

    return QString("%1m %2s %3ms").arg(minutes).arg(seconds).arg(ms);
}

void MainWindow::ClearPuzzleLayout() {
    QLayoutItem *item;
    while ((item = ui->puzzleGridLayout->takeAt(0)) != nullptr) {
        if (item->widget())
            delete item->widget();
        delete item;
    }
}

void MainWindow::DisplayMessagePuzzleLayout(const QString& message) {
    QLabel *label = new QLabel(message, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 18px; color: red;");
    ui->puzzleGridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignCenter);
}
