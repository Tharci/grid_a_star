#ifndef A_STAR_H
#define A_STAR_H

#include <math.h>
#include <iostream>

#include "grid.h"
#include "linked_list.h"
#include "node.h"


class Application;


class Graph
{
public:
    Graph(Application* app, Grid<Node>* map);
    ~Graph();

    void findPath(Node* startNode, Node* endNode);
    void newOpenNode(Node* node);
    int nodeIdxInOpen(Node* node);
    int disFromEndNode(Node* node);

    void clearPathSearch();

    Node* startNode;
    Node* endNode;

    bool pathFound = false;

    LinkedList<Node*>* openNodes;

    void cleanUp();

private:
    Grid<Node>* map;

    Application* app;
};


#endif