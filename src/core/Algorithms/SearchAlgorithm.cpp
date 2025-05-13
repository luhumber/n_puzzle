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

QVector<Node> SearchAlgorithm::ExpandNeighbors(const Node& node, const QVector<int>& goal, bool withParent) const {
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
            float g = node.getGCost() + 1;
            float h = ComputeHeuristic(newState, goal);
            std::shared_ptr<Node> parent = withParent ? std::make_shared<Node>(node) : nullptr;
            neighbors.append(Node(newState, g, h, parent));
        }
    }
    return neighbors;
}

QString SearchAlgorithm::StateToString(const QVector<int>& state) const {
    QString str;
    for (int value : state) {
        str += QString::number(value) + ",";
    }
    return str;
}

bool SearchAlgorithm::IsStopRequested() const {
    return _stop_requested && *_stop_requested;
}
