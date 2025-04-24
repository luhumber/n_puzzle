#pragma once

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    bool            _is_solvable;
    int             _puzzle_size;
    QVector<int>    _puzzle_vector;

    void ParseOutput(const QString &output);
    void DisplayPuzzle();
    
private slots:
    void CreatePuzzle();
};
