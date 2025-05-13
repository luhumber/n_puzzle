#include "IDAStar.h"
#include <limits>
#include <QSet>
#include <QVector>
#include <algorithm>

QVector<QVector<int>> IDAStar::Solve(const QVector<int>& initial_state, const QVector<int>& goal) {
    _states_tested = 0;
    float bound = ComputeHeuristic(initial_state, goal);
    QVector<QVector<int>> path;
    path.append(initial_state);

    while (true) {
        if (IsStopRequested())
            return {};
        float t = Search(path, 0, bound, goal);
        if (t == -1) {
            return path;
        }
        if (t == std::numeric_limits<float>::infinity())
            return {};
        bound = t;
    }
}

float IDAStar::Search(QVector<QVector<int>>& path, float g, float bound, const QVector<int>& goal) {
    if (IsStopRequested())
        return std::numeric_limits<float>::infinity();

    UpdateMaxStatesInMemory(path.size());
    const QVector<int>& node = path.last();
    float f = g + ComputeHeuristic(node, goal);
    if (f > bound)
        return f;
    if (node == goal)
        return -1;
    ++_states_tested;

    float min = std::numeric_limits<float>::infinity();
    QVector<Node> neighbors = ExpandNeighbors(Node(node, g, 0, nullptr), goal, false);

    std::sort(neighbors.begin(), neighbors.end(), [&](const Node& a, const Node& b) {
        return ComputeHeuristic(a.getState(), goal) < ComputeHeuristic(b.getState(), goal);
    });

    for (Node& neighbor : neighbors) {
        if (IsStopRequested())
            return std::numeric_limits<float>::infinity();
        bool in_path = std::any_of(path.begin(), path.end(), [&](const QVector<int>& s) {
            return s == neighbor.getState();
        });
        if (in_path)
            continue;
        path.append(neighbor.getState());
        float t = Search(path, g + 1, bound, goal);
        if (t == -1)
            return -1;
        if (t < min)
            min = t;
        path.removeLast();
    }
    return min;
}
