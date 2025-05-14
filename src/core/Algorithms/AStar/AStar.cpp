#include "AStar.h"
#include "Metrics.h"
#include <limits>
#include <algorithm>
#include <QSet>
#include <QString>
#include <QMultiMap>

QVector<QVector<int>> AStar::Solve(const QVector<int>& initial_state, const QVector<int>& goal) {
    _states_tested = 0;

    QMultiMap<float, Node> open_list;
    QSet<QString> closed_set;
    QHash<QString, float> open_set_g;

    float h = this->ComputeHeuristic(initial_state, goal);
    Node start_node(initial_state, 0.0f, h, nullptr);

    open_list.insert(start_node.getFCost(), start_node);
    open_set_g[this->StateToString(initial_state)] = 0.0f;

    while (!open_list.isEmpty()) {
        if (this->IsStopRequested())
            return {};
        this->UpdateMaxStatesInMemory(open_list.size() + closed_set.size());
        auto it = open_list.begin();
        Node current = it.value();
        open_list.erase(it);

        ++_states_tested;

        QString current_hash = this->StateToString(current.getState());
        if (closed_set.contains(current_hash))
            continue;
        closed_set.insert(current_hash);

        if (current.getState() == goal) {
            QVector<QVector<int>> path;
            std::shared_ptr<Node> node = std::make_shared<Node>(current);
            while (node) {
                path.append(node->getState());
                node = node->getParent();
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        QVector<Node> neighbors = this->ExpandNeighbors(current, goal, true);
        for (Node& neighbor : neighbors) {
            if (this->IsStopRequested())
                return {};
            QString neighbor_hash = this->StateToString(neighbor.getState());
            if (closed_set.contains(neighbor_hash))
                continue;

            float g = neighbor.getGCost();
            if (!open_set_g.contains(neighbor_hash) || g < open_set_g[neighbor_hash]) {
                open_list.insert(neighbor.getFCost(), neighbor);
                open_set_g[neighbor_hash] = g;
            }
        }
    }
    return {};
}
