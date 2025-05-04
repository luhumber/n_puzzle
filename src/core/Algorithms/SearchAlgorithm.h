#pragma once

#include "Node.h"
#include "Metrics.h"

class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() = default;
    virtual QVector<QVector<int>> solve(const QVector<int>& initial_state, const QVector<int>& goal) = 0;
    void setHeuristic(HeuristicType h) { _heuristic = h; }

    qint64 _states_tested = 0;
    qint64 getStatesTested() const { return _states_tested; }

protected:
    HeuristicType _heuristic = HeuristicType::Manhattan;
    virtual QVector<Node> expandNeighbors(const Node& node, const QVector<int>& goal) = 0;
    
    float ComputeHeuristic(const QVector<int>& current, const QVector<int>& goal) const;
};
