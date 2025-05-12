#pragma once

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QRegularExpression>

#include "Solver.h"
#include "AStar.h"
#include "PuzzleParser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow*         ui;
    bool                    _is_solvable;
    int                     _puzzle_size;
    QVector<int>            _puzzle_vector;
    std::shared_ptr<Solver> _solver;
    QVector<QVector<int>>   _solved_puzzle;
    int                     _current_state_index;
    PuzzleParser            _parser;

    bool    ParseOutput(const QString &output);
    void    DisplayPuzzle(const QVector<int>& puzzle);
    QString FormatElapsedTime(qint64 elapsed_ms);
    void    ClearPuzzleLayout();
    void    DisplayMessagePuzzleLayout(const QString& message);
    
private slots:
    void on_CreatePuzzleButtonClicked();
    void on_ChoosePuzzleButtonClicked();
    void on_StartButtonClicked();
    void on_InitialStateButtonClicked();
    void on_GoalStateButtonClicked();
    void on_BackButtonClicked();
    void on_NextButtonClicked();

public slots:
    void on_PuzzleSolved(const QVector<QVector<int>>& solved_puzzle, qint64 elapsed_ms, qint64 states_tested, qint64 max_states_in_memory);

signals:
    void signal_PuzzleCreated(const QVector<int>& puzzle, int size, const QString& heuristic);
};
