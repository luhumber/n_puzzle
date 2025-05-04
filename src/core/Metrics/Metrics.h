#pragma once

#include <QVector>
#include <QHash>

enum class HeuristicType {
    Manhattan,
    Hamming,
    ManhattanPlusLC
};

class Metrics {
    public:
        static HeuristicType selectHeuristic(const QString& heuristic);
        static float calculateManhattanDistance(const QVector<int>& current, const QVector<int>& goal);
        static float calculateHammingDistance(const QVector<int>& current, const QVector<int>& goal);
        static float calculateManhattanPlusLC(const QVector<int>& current, const QVector<int>& goal);
    };
    