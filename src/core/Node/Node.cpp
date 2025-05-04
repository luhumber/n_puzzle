#include "Node.h"

Node::Node(const QVector<int>& state, float gCost, float hCost, std::shared_ptr<Node> parent)
    : state(state), gCost(gCost), hCost(hCost), parent(std::move(parent)) {}

const QVector<int>& Node::getState() const {
    return state;
}

float Node::getGCost() const {
    return gCost;
}

float Node::getHCost() const {
    return hCost;
}

float Node::getFCost() const {
    return gCost + hCost;
}

std::shared_ptr<Node> Node::getParent() const {
    return parent;
}

void Node::setParent(std::shared_ptr<Node> newParent) {
    parent = std::move(newParent);
}

bool Node::operator==(const Node& other) const {
    return state == other.state;
}
