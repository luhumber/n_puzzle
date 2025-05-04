#include "SearchAlgorithm.h"

float SearchAlgorithm::ComputeHeuristic(const QVector<int>& current, const QVector<int>& goal) const {
    switch (_heuristic) {
        case HeuristicType::Manhattan:
            return Metrics::calculateManhattanDistance(current, goal);
        case HeuristicType::Hamming:
            return Metrics::calculateHammingDistance(current, goal);
        case HeuristicType::ManhattanPlusLC:
            return Metrics::calculateManhattanPlusLC(current, goal);
    }
    return 0.0f;
}
