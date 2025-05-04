#include "AStar.h"
#include "Metrics.h"
#include <limits>
#include <algorithm>
#include <QSet>
#include <QString>
#include <QMultiMap>

QString stateToString(const QVector<int>& state) {
    QString s;
    for (int v : state) s += QString::number(v) + ",";
    return s;
}

QVector<QVector<int>> AStar::solve(const QVector<int>& initial_state, const QVector<int>& goal) {
    qDebug() << "Initial state:" << initial_state;
    qDebug() << "Goal state:" << goal;
    _states_tested = 0;

    QMultiMap<float, Node> openList;
    QSet<QString> closedSet;
    QHash<QString, float> openSetG;
    
    float h = ComputeHeuristic(initial_state, goal);
    Node startNode(initial_state, 0.0f, h, nullptr);
    
    openList.insert(startNode.getFCost(), startNode);
    openSetG[stateToString(initial_state)] = 0.0f;
    
    while (!openList.isEmpty()) {
        auto it = openList.begin();
        Node current = it.value();
        openList.erase(it);

        ++_states_tested;
    
        QString currentHash = stateToString(current.getState());
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
    
        QVector<Node> neighbors = expandNeighbors(current, goal);
        for (Node& neighbor : neighbors) {
            QString neighborHash = stateToString(neighbor.getState());
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

QVector<Node> AStar::expandNeighbors(const Node& node, const QVector<int>& goal) {
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
            neighbors.append(Node(newState, g, h, std::make_shared<Node>(node)));
        }
    }
    return neighbors;
}
