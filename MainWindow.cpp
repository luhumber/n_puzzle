#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->createPuzzlePushButton, &QPushButton::clicked, this, &MainWindow::createPuzzle);
}

MainWindow::~MainWindow() {
    disconnect(ui->createPuzzlePushButton, &QPushButton::clicked, this, &MainWindow::createPuzzle);
    delete ui;
}

void MainWindow::createPuzzle() {
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
    qDebug() << "Output:" << output;

    this->parseOutput(output);
    this->displayPuzzle();

    return;
}

void MainWindow::parseOutput(const QString &output) {
    QTextStream stream(const_cast<QString*>(&output));
    QString line;

    line = stream.readLine();
    bool is_solvable = !line.contains("unsolvable", Qt::CaseInsensitive);
    if (!is_solvable) {
        qDebug() << "Puzzle is unsolvable.";
        return;
    }

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

    qDebug() << "Puzzle size:" << _puzzle_size;
    qDebug() << "Puzzle (linear):" << _puzzle_vector;
}

void MainWindow::displayPuzzle() {
    QLayoutItem *item;
    while ((item = ui->puzzleGridLayout->takeAt(0)) != nullptr) {
        if (item->widget())
            delete item->widget();
        delete item;
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
