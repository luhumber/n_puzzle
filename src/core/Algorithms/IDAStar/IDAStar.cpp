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
        if (_stop_requested && *_stop_requested)
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
    if (_stop_requested && *_stop_requested)
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
    QVector<Node> neighbors = ExpandNeighbors(Node(node, g, 0, nullptr), goal);

    std::sort(neighbors.begin(), neighbors.end(), [&](const Node& a, const Node& b) {
        return ComputeHeuristic(a.getState(), goal) < ComputeHeuristic(b.getState(), goal);
    });

    for (Node& neighbor : neighbors) {
        if (_stop_requested && *_stop_requested)
            return std::numeric_limits<float>::infinity();
        bool inPath = std::any_of(path.begin(), path.end(), [&](const QVector<int>& s) {
            return s == neighbor.getState();
        });
        if (inPath)
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

QVector<Node> IDAStar::ExpandNeighbors(const Node& node, const QVector<int>& goal) {
    QVector<Node> neighbors;
    const QVector<int>& state = node.getState();
    int size = static_cast<int>(std::sqrt(state.size()));
    int zeroIdx = state.indexOf(0);
    int row = zeroIdx / size;
    int col = zeroIdx % size;

    QVector<QPair<int, int>> moves = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    for (const auto& move : moves) {
        int newRow = row + move.first;
        int newCol = col + move.second;
        if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
            int newIdx = newRow * size + newCol;
            QVector<int> newState = state;
            std::swap(newState[zeroIdx], newState[newIdx]);
            neighbors.append(Node(newState, node.getGCost() + 1, 0, nullptr));
        }
    }
    return neighbors;
}

QString IDAStar::StateToString(const QVector<int>& state) const {
    QString str;
    for (int value : state) {
        str += QString::number(value) + ",";
    }
    return str;
}