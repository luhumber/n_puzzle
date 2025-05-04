#pragma once

#include "SearchAlgorithm.h"
#include "Node.h"
#include "Metrics.h"

#include <QSet>
#include <QVector>
#include <QDebug>

class IDAStar : public SearchAlgorithm {
public:
    QVector<QVector<int>> solve(const QVector<int>& initial_state, const QVector<int>& goal) override;

protected:
    QVector<Node> expandNeighbors(const Node& node, const QVector<int>& goal) override;

private:
    float   search(QVector<QVector<int>>& path, float g, float bound, const QVector<int>& goal);
    QString stateToString(const QVector<int>& state) const;
};