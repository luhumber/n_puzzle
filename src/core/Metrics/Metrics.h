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
        static HeuristicType    SelectHeuristic(const QString& heuristic);
        static float            CalculateManhattanDistance(const QVector<int>& current, const QVector<int>& goal);
        static float            CalculateHammingDistance(const QVector<int>& current, const QVector<int>& goal);
        static float            CalculateManhattanPlusLC(const QVector<int>& current, const QVector<int>& goal);
    };
    