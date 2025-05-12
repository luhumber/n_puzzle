#pragma once

#include <QVector>
#include <QObject>
#include <QDebug>
#include <QElapsedTimer>
#include <QtConcurrent>

#include "SearchAlgorithm.h"
#include "AStar.h"
#include "IDAStar.h"

class Solver : public QObject {
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);
    void     InitSolver();
    void     setAlgorithm(std::shared_ptr<SearchAlgorithm> algorithm);
    
private:
    int                                 _size;
    QVector<int>                        _initial_state;
    QVector<int>                        _goal;
    std::shared_ptr<SearchAlgorithm>    _algorithm;
    QString                             _heuristic;
    QVector<QVector<int>>               _puzzle_solved;
    
    void    GenerateGoal();
    void    DecideAlgorithm();

public slots:
    void    on_PuzzleCreated(const QVector<int>& puzzle, int size, const QString& heuristic);

signals:
    void    signal_PuzzleSolved(const QVector<QVector<int>>& solved_puzzle, qint64 elapsed_ms, qint64 states_tested, quint64 max_states_in_memory);
};
