#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->createPuzzlePushButton, &QPushButton::clicked, this, &MainWindow::CreatePuzzle);
}

MainWindow::~MainWindow() {
    disconnect(ui->createPuzzlePushButton, &QPushButton::clicked, this, &MainWindow::CreatePuzzle);
    delete ui;
}

void MainWindow::CreatePuzzle() {
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
    this->ParseOutput(output);

    this->DisplayPuzzle();
}

void MainWindow::ParseOutput(const QString &output) {
    QTextStream stream(const_cast<QString*>(&output));
    QString line;

    line = stream.readLine();
    if ((_is_solvable = !line.contains("unsolvable", Qt::CaseInsensitive)) == false)
        return;

    line = stream.readLine();
    _puzzle_size = line.toInt();

    _puzzle_vector.clear();
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.isEmpty()) continue;

        QStringList numbers = line.split(" ", Qt::SkipEmptyParts);
        for (const QString &num : numbers) {
            _puzzle_vector.append(num.toInt());
        }
    }
}

void MainWindow::DisplayPuzzle() {
    QLayoutItem *item;
    while ((item = ui->puzzleGridLayout->takeAt(0)) != nullptr) {
        if (item->widget())
            delete item->widget();
        delete item;
    }

    if (!_is_solvable) {
        QLabel *label = new QLabel("The puzzle is unsolvable.", this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 18px; color: red;");
        ui->puzzleGridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignCenter);
        return;
    }

    for (int i = 0; i < _puzzle_size; ++i) {
        for (int j = 0; j < _puzzle_size; ++j) {
            int index = i * _puzzle_size + j;
            int value = _puzzle_vector[index];

            QPushButton *button = new QPushButton(value == 0 ? "" : QString::number(value), this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            if (value == 0)
                button->setVisible(false);
            ui->puzzleGridLayout->addWidget(button, i, j);
        }
    }

    ui->puzzleGridLayout->update();
}
