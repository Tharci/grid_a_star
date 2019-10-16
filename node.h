#ifndef NODE_H
#define NODE_H

struct Node
{
    Node();

    int x, y;
    int dis_s = 0;
    int dis_e = 0;
    int value();

    bool open = false;
    bool closed = false;

    Node* parentNode = nullptr;

    char dValue = 0;

    void clear();
    void clearPath();
};

#endif