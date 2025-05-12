#pragma once

#include "SearchAlgorithm.h"
#include "Node.h"
#include <QQueue>
#include <QSet>

#include <QDebug>

class AStar : public SearchAlgorithm {
public:
    QVector<QVector<int>>   Solve(const QVector<int>& initial_state, const QVector<int>& goal) override;

protected:
    QVector<Node>   ExpandNeighbors(const Node& node, const QVector<int>& goal) override;

private:
    QQueue<Node>    _openList;
    QVector<Node>   _closedList;
};