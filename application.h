#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "grid.h"
#include "linked_list.h"
#include "node.h"



class Graph;


class Application
{
public:
    Application();
    ~Application();

    void init(const char* title, int xpos, int ypos, bool fullscreen, int window_width, int window_height, int nodeSize);
    
    void handleEvents();
    void update();
    void render();
    void renderGrid();
    void clean();
    void colorNode(int x, int y, std::string color);

    void findPath();

    void clearScreen();

    bool running();

    bool escPressed(); //interrupt listener for graph class
    void getMouseCoors(int* x, int* y);
    void changeNodeOnMap(int x, int y, char value);
    void drawLineOnNodes(int from[], int to[], char putOrRemove);


    bool screenChanged = true;

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    int windowWidth;
    int windowHeight;
    int nodeSize;
    int gapSize = 1;

    bool change_start_end = true;
    Node* startNode = nullptr;
    Node* endNode = nullptr;
    
    Grid<Node>* map;

    int mouse_left_1[2] = {-1, -1};
    int mouse_left_2[2] = {-1, -1};
    bool mouse_left_write_1 = true;

    int mouse_right_1[2] = {-1, -1};
    int mouse_right_2[2] = {-1, -1};
    bool mouse_right_write_1 = true;

    Graph* graph;
};


#endif