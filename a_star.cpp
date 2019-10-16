#include "a_star.h"
#include "application.h"
#include "arg_handling.h"



Graph::Graph(Application* app, Grid<Node>* map) 
{
    this->app = app;
    this->map = map;

    openNodes = new LinkedList<Node*>();
}


Graph::~Graph() 
{
    delete openNodes;
}


void Graph::findPath(Node* startNode, Node* endNode)
{
    clearPathSearch();

    this->startNode = startNode;
    this->endNode = endNode;

    endNode->dValue = 0;
    startNode->dValue = 0;

    this->startNode->dis_e = disFromEndNode(this->startNode);
    this->startNode->open = true;
    newOpenNode(startNode);

    Node* currNode;

    bool interrupt = false;
    int renderCounter = 0;

    while (!(currNode == endNode) && !interrupt)
    {
        if (openNodes->size() == 0)
        {
            std::cout << "No path avaible from startPoint to endPoint. :c\n";
            return;
        }
        currNode = openNodes->get(0);
        openNodes->remove(0);
        
        currNode->open = false;
        currNode->closed = true;

        if (currNode == endNode)
        {
            std::cout << "Path has been found.\n";
            pathFound = true;
            break;
        }


        int neighbours[4][2] = 
        {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };

        for (int i = 0; i < 4; i++)
        {
            int x = currNode->x + neighbours[i][0];
            int y = currNode->y + neighbours[i][1];

            Node* nextNode;
            bool jump = true;

            if ( !map->checkXY(x, y) )
            {
                jump = false;
            }
            else 
            {
                nextNode =  map->get(x, y);

                if (nextNode->dValue == 1)
                    jump = false;
                else if (nextNode->closed)
                    jump = false;
            }


            if (jump)
            {
                if (!nextNode->open)
                {
                    nextNode->dis_s = currNode->dis_s + 1;
                    nextNode->dis_e = disFromEndNode(nextNode);
                    newOpenNode(nextNode);
                    nextNode->open = true;
                    nextNode->parentNode = currNode;

                    //PROGRESS RENDER
                    if (renderCounter++ % refreshRate == refreshRate - 1)
                    {
                        app->screenChanged = true;
                        app->render();
                        renderCounter = 0;
                    }
                    SDL_Delay(animDelay);
                }
                else if (currNode->dis_s + 1 < nextNode->dis_s)
                {
                    nextNode->dis_s = currNode->dis_s + 1;
                    nextNode->parentNode = currNode;
                    
                    openNodes->remove(nodeIdxInOpen(nextNode));
                    newOpenNode(nextNode);
                }
            }
        }

        

        //INTERRUPT LISTENER
        if (interrupt = app->escPressed())
        {
            clearPathSearch();
        }
    }
}

void Graph::newOpenNode(Node* node)
{
    int i = 0;
    while ( (i < openNodes->size()) && (node->value() > openNodes->get(i)->value()) ) //ÉS g KISEBB!!
    {
        ++i;
    }
    
    if (i == openNodes->size())
    {
        openNodes->append(node);
    }
    else
    {
        openNodes->insert(node, i);
    }
    
}

int Graph::nodeIdxInOpen(Node* node)
{
    for (int i = 0; i < openNodes->size(); ++i)
    {
        if (openNodes->get(i) == node)
        {
            return i;
        }
            
    }

    return -1;
}

int Graph::disFromEndNode(Node* node)
{
    return abs(endNode->x - node->x) + abs(endNode->y - node->y);
}


void Graph::cleanUp()
{
    startNode = nullptr;
    endNode = nullptr;
    openNodes->clear();

    for (int x = 0; x < map->getWidth(); ++x)
    {
        for (int y = 0; y < map->getHeight(); ++y)
        {
            map->get(x, y)->clear();
        }
    }

    pathFound = false;
}

void Graph::clearPathSearch()
{
    openNodes->clear();
    endNode = nullptr;
    app->screenChanged = true;

    for (int x = 0; x < map->getWidth(); ++x)
    {
        for (int y = 0; y < map->getHeight(); ++y)
        {
            map->get(x, y)->clearPath();
        }
    }

    pathFound = false;
}



