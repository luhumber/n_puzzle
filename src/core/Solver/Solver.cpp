#include "Solver.h"
#include <QDebug>

Solver::Solver(QObject *parent)
    : QObject(parent) {}

void Solver::InitSolver() {
    if (!_algorithm) {
        this->DecideAlgorithm();
    }
    this->GenerateGoal();

    QElapsedTimer timer;
    timer.start();

    _algorithm->setHeuristic(Metrics::selectHeuristic(_heuristic));
    _puzzle_solved = _algorithm->solve(_initial_state, _goal);

    qint64 elapsed_ms = timer.elapsed();
    emit signal_PuzzleSolved(_puzzle_solved, elapsed_ms, _algorithm->getStatesTested());
}

void Solver::DecideAlgorithm() {
    if (_size < 5) {
        _algorithm = std::make_shared<AStar>();
    } else {
        _algorithm = std::make_shared<IDAStar>();
    }
}

void Solver::setAlgorithm(std::shared_ptr<SearchAlgorithm> algorithm) {
    _algorithm = std::move(algorithm);
}

void Solver::GenerateGoal() {
    QVector<int> goal(_size * _size, 0);
    int value = 1;
    int top = 0, bottom = _size - 1, left = 0, right = _size - 1;

    while (value < _size * _size) {
        for (int i = left; i <= right && value < _size * _size; ++i) {
            goal[top * _size + i] = value++;
        }
        ++top;

        for (int i = top; i <= bottom && value < _size * _size; ++i) {
            goal[i * _size + right] = value++;
        }
        --right;

        for (int i = right; i >= left && value < _size * _size; --i) {
            goal[bottom * _size + i] = value++;
        }
        --bottom;

        for (int i = bottom; i >= top && value < _size * _size; --i) {
            goal[i * _size + left] = value++;
        }
        ++left;
    }

    if (_size % 2 != 0) {
        int center = (_size / 2) * _size + (_size / 2);
        goal[center] = 0;
    }

    _goal = goal;
}

void Solver::on_PuzzleCreated(const QVector<int>& puzzle, int size, const QString& heuristic) {
    _initial_state = puzzle;
    _size = size;
    _heuristic = heuristic;

    (void)QtConcurrent::run([this]() { this->InitSolver(); });
}
