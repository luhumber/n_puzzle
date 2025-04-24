#pragma once

struct Node
{
    int x;
    int y;
    float heuristic;
};

class Algorithms
{
public:
    Algorithms();
    ~Algorithms();

    void AStar();
    void IDAStar();

private:
    Node currentNode;
};
