#pragma once
#include <QVector>
#include <memory>

class Node {
public:
    Node(const QVector<int>& state, float gCost = 0.0f, float hCost = 0.0f, std::shared_ptr<Node> parent = nullptr);

    const QVector<int>& getState() const;
    float getGCost() const;
    float getHCost() const;
    float getFCost() const;
    std::shared_ptr<Node> getParent() const;

    void setParent(std::shared_ptr<Node> parent);

    bool operator==(const Node& other) const;

private:
    QVector<int> state;
    float gCost;
    float hCost;
    std::shared_ptr<Node> parent;
};
