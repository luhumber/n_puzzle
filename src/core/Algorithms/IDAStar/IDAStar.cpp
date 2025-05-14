#include "IDAStar.h"
#include <limits>
#include <QSet>
#include <QVector>
#include <algorithm>

QVector<QVector<int>> IDAStar::Solve(const QVector<int>& initial_state, const QVector<int>& goal) {
    _states_tested = 0;
    float bound = this->ComputeHeuristic(initial_state, goal);
    QVector<QVector<int>> path;
    path.append(initial_state);

    while (true) {
        if (this->IsStopRequested())
            return {};
        float result = this->Search(path, 0, bound, goal);
        if (result == -1) {
            return path;
        }
        if (result == std::numeric_limits<float>::infinity())
            return {};
        bound = result;
    }
}

float IDAStar::Search(QVector<QVector<int>>& path, float g, float bound, const QVector<int>& goal) {
    if (this->IsStopRequested())
        return std::numeric_limits<float>::infinity();

    this->UpdateMaxStatesInMemory(path.size());
    const QVector<int>& node = path.last();
    float f = g + this->ComputeHeuristic(node, goal);
    if (f > bound)
        return f;
    if (node == goal)
        return -1;
    ++_states_tested;

    float min = std::numeric_limits<float>::infinity();
    QVector<Node> neighbors = this->ExpandNeighbors(Node(node, g, 0, nullptr), goal, false);

    std::sort(neighbors.begin(), neighbors.end(), [&](const Node& a, const Node& b) {
        return this->ComputeHeuristic(a.getState(), goal) < this->ComputeHeuristic(b.getState(), goal);
    });

    for (Node& neighbor : neighbors) {
        if (this->IsStopRequested())
            return std::numeric_limits<float>::infinity();
        bool in_path = std::any_of(path.begin(), path.end(), [&](const QVector<int>& s) {
            return s == neighbor.getState();
        });
        if (in_path)
            continue;
        path.append(neighbor.getState());
        float result = this->Search(path, g + 1, bound, goal);
        if (result == -1)
            return -1;
        if (result < min)
            min = result;
        path.removeLast();
    }
    return min;
}
