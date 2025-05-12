#pragma once

#include "Node.h"
#include "Metrics.h"

class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() = default;
    virtual QVector<QVector<int>> Solve(const QVector<int>& initial_state, const QVector<int>& goal) = 0;
    
    void    setHeuristic(HeuristicType h) { _heuristic = h; }
    qint64  getStatesTested() const { return _states_tested; }
    qint64  getMaxStatesInMemory() const { return _max_states_in_memory; }
    void    setMaxStatesInMemory(int max_states) { _max_states_in_memory = max_states; }
    
    protected:
    qint64          _max_states_in_memory = 0;
    qint64          _states_tested = 0;
    HeuristicType   _heuristic = HeuristicType::Manhattan;
    
    void    UpdateMaxStatesInMemory(qint64 current_states_in_memory);
    float   ComputeHeuristic(const QVector<int>& current, const QVector<int>& goal) const;
    virtual QVector<Node> ExpandNeighbors(const Node& node, const QVector<int>& goal) = 0;
};
