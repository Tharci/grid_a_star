#include "node.h"


Node::Node() {}


int Node::value()
{
    return this->dis_s + this->dis_e;
}

void Node::clear()
{
    dValue = 0;
    open = false;
    closed = false;
}

void Node::clearPath()
{
    open = false;
    closed = false;
}