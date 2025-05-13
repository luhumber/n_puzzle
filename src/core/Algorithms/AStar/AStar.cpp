#include "AStar.h"
#include "Metrics.h"
#include <limits>
#include <algorithm>
#include <QSet>
#include <QString>
#include <QMultiMap>

QVector<QVector<int>> AStar::Solve(const QVector<int>& initial_state, const QVector<int>& goal) {
    _states_tested = 0;

    QMultiMap<float, Node> openList;
    QSet<QString> closedSet;
    QHash<QString, float> openSetG;

    float h = ComputeHeuristic(initial_state, goal);
    Node startNode(initial_state, 0.0f, h, nullptr);

    openList.insert(startNode.getFCost(), startNode);
    openSetG[StateToString(initial_state)] = 0.0f;

    while (!openList.isEmpty()) {
        if (IsStopRequested())
            return {};
        UpdateMaxStatesInMemory(openList.size() + closedSet.size());
        auto it = openList.begin();
        Node current = it.value();
        openList.erase(it);

        ++_states_tested;

        QString currentHash = StateToString(current.getState());
        if (closedSet.contains(currentHash))
            continue;
        closedSet.insert(currentHash);

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

        QVector<Node> neighbors = ExpandNeighbors(current, goal, true);
        for (Node& neighbor : neighbors) {
            if (IsStopRequested())
                return {};
            QString neighborHash = StateToString(neighbor.getState());
            if (closedSet.contains(neighborHash))
                continue;

            float g = neighbor.getGCost();
            if (!openSetG.contains(neighborHash) || g < openSetG[neighborHash]) {
                openList.insert(neighbor.getFCost(), neighbor);
                openSetG[neighborHash] = g;
            }
        }
    }
    return {};
}
