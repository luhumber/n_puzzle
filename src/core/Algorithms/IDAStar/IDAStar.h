#pragma once

#include "SearchAlgorithm.h"
#include "Node.h"
#include "Metrics.h"

#include <QSet>
#include <QVector>

class IDAStar : public SearchAlgorithm {
public:
    QVector<QVector<int>> Solve(const QVector<int>& initial_state, const QVector<int>& goal) override;

protected:
    QVector<Node> ExpandNeighbors(const Node& node, const QVector<int>& goal) override;
    float   Search(QVector<QVector<int>>& path, float g, float bound, const QVector<int>& goal);
    QString StateToString(const QVector<int>& state) const;
};