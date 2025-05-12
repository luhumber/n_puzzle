#include "SearchAlgorithm.h"

void SearchAlgorithm::UpdateMaxStatesInMemory(qint64 current_states_in_memory) {
    if (current_states_in_memory > _max_states_in_memory) {
        _max_states_in_memory = current_states_in_memory;
    }
}

float SearchAlgorithm::ComputeHeuristic(const QVector<int>& current, const QVector<int>& goal) const {
    switch (_heuristic) {
        case HeuristicType::Manhattan:
            return Metrics::CalculateManhattanDistance(current, goal);
        case HeuristicType::Hamming:
            return Metrics::CalculateHammingDistance(current, goal);
        case HeuristicType::ManhattanPlusLC:
            return Metrics::CalculateManhattanPlusLC(current, goal);
    }
    return 0.0f;
}
