#include "Metrics.h"
#include <cmath>
#include <QHash>
#include <algorithm>

HeuristicType Metrics::SelectHeuristic(const QString& heuristic) {
    if (heuristic == "Manhattan Distance") {
        return HeuristicType::Manhattan;
    } else if (heuristic == "Hamming Distance") {
        return HeuristicType::Hamming;
    } else if (heuristic == "Manhattan Plus LC") {
        return HeuristicType::ManhattanPlusLC;
    }
    return HeuristicType::Manhattan;
}

float Metrics::CalculateManhattanDistance(const QVector<int>& current, const QVector<int>& goal) {
    int size = static_cast<int>(std::sqrt(current.size()));
    float distance = 0.0f;

    static thread_local QHash<int, int> goal_positions;
    goal_positions.clear();
    for (int i = 0; i < goal.size(); ++i) {
        goal_positions[goal[i]] = i;
    }

    for (int i = 0; i < current.size(); ++i) {
        int value = current[i];
        if (value == 0) continue;
        int goal_index = goal_positions[value];
        distance += std::abs(i / size - goal_index / size) + std::abs(i % size - goal_index % size);
    }
    return distance;
}

float Metrics::CalculateHammingDistance(const QVector<int>& current, const QVector<int>& goal) {
    int count = 0;
    for (int i = 0; i < current.size(); ++i) {
        if (current[i] != 0 && current[i] != goal[i])
            ++count;
    }
    return static_cast<float>(count);
}

float Metrics::CalculateManhattanPlusLC(const QVector<int>& current, const QVector<int>& goal) {
    int size = static_cast<int>(std::sqrt(current.size()));
    float manhattan = CalculateManhattanDistance(current, goal);

    QHash<int, int> goal_positions;
    for (int i = 0; i < goal.size(); ++i) {
        goal_positions[goal[i]] = i;
    }

    int linear_conflict = 0;

    for (int row = 0; row < size; ++row) {
        QVector<int> current_row;
        QVector<int> goalRow(size, -1);
        for (int col = 0; col < size; ++col) {
            int idx = row * size + col;
            int value = current[idx];
            if (value != 0 && (goal_positions[value] / size) == row) {
                current_row.append(value);
            }
        }
        for (int i = 0; i < current_row.size(); ++i) {
            int vi = current_row[i];
            int goal_col_i = goal_positions[vi] % size;
            for (int j = i + 1; j < current_row.size(); ++j) {
                int vj = current_row[j];
                int goal_col_j = goal_positions[vj] % size;
                if (goal_col_i > goal_col_j)
                    linear_conflict += 2;
            }
        }
    }

    for (int col = 0; col < size; ++col) {
        QVector<int> current_col;
        for (int row = 0; row < size; ++row) {
            int idx = row * size + col;
            int value = current[idx];
            if (value != 0 && (goal_positions[value] % size) == col) {
                current_col.append(value);
            }
        }
        for (int i = 0; i < current_col.size(); ++i) {
            int vi = current_col[i];
            int goal_row_i = goal_positions[vi] / size;
            for (int j = i + 1; j < current_col.size(); ++j) {
                int vj = current_col[j];
                int goal_row_j = goal_positions[vj] / size;
                if (goal_row_i > goal_row_j)
                    linear_conflict += 2;
            }
        }
    }

    return manhattan + linear_conflict;
}