#pragma once

#include "SearchAlgorithm.h"
#include "Node.h"
#include <QQueue>
#include <QSet>

class AStar : public SearchAlgorithm {
public:
    QVector<QVector<int>>   Solve(const QVector<int>& initial_state, const QVector<int>& goal) override;

private:
    QQueue<Node>    _openList;
    QVector<Node>   _closedList;
};