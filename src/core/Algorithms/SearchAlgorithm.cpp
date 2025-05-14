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
    int zero_idx = state.indexOf(0);
    int row = zero_idx / size;
    int col = zero_idx % size;

    QVector<QPair<int, int>> moves = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    for (const auto& move : moves) {
        int new_row = row + move.first;
        int new_col = col + move.second;
        if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size) {
            int newIdx = new_row * size + new_col;
            QVector<int> new_state = state;
            std::swap(new_state[zero_idx], new_state[newIdx]);
            float g = node.getGCost() + 1;
            float h = this->ComputeHeuristic(new_state, goal);
            std::shared_ptr<Node> parent = withParent ? std::make_shared<Node>(node) : nullptr;
            neighbors.append(Node(new_state, g, h, parent));
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
