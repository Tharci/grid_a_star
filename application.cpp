#include "application.h"
#include "a_star.h"

Application::Application() {}

Application::~Application() {}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

void Application::init(const char* title, int xpos, int ypos, bool fullscreen, int window_width, int window_height, int nodeSize)
{
    windowWidth = window_width;
    windowHeight = window_height;

    if (nodeSize > min(windowWidth, windowHeight) / 2)
    {
        nodeSize = (int) (min(windowWidth, windowHeight) / 2) - 2;
    }
    this->nodeSize = nodeSize;

    windowWidth = window_width - window_width % (nodeSize + gapSize) + 1;
    windowHeight = window_height - window_height % (nodeSize + gapSize) + 1;

    
    map = new Grid<Node>(windowWidth / (nodeSize + gapSize), windowHeight / (nodeSize + gapSize));
    for (int x = 0; x < map->getWidth(); ++x)
    {
        for (int y = 0; y < map->getHeight(); ++y)
        {
            map->get(x, y)->x  = x;
            map->get(x, y)->y  = y;
        }
    }

    graph = new Graph(this, map);


    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initalised.\n";

        window = SDL_CreateWindow(title, xpos, ypos, windowWidth, windowHeight, flags);
        if (window)
        {
            std::cout << "Window created.\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created.\n\n";
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
}

void Application::handleEvents()
{
    SDL_Event event;

    while( SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
            case SDLK_RETURN:
                this->findPath();
                break;

            case SDLK_BACKSPACE:
                this->clearScreen();
                break;

            case SDLK_a:
                //put start/end node
                int nodeX, nodeY;
                getMouseCoors(&nodeX, &nodeY);

                if (nodeX == map->getWidth())
                    nodeX = map->getWidth() - 1;
                if (nodeY == map->getHeight())
                    nodeY = map->getHeight() - 1;

                if (change_start_end)
                {
                    startNode = map->get(nodeX, nodeY);
                }
                else
                {
                    endNode = map->get(nodeX, nodeY);
                }

                change_start_end = !change_start_end;
                screenChanged = true;

                break;

            case SDLK_r: //RESET
                graph->clearPathSearch();
                break;
            }
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                if (mouse_left_write_1)
                    getMouseCoors(&mouse_left_1[0], &mouse_left_1[1]);
                else
                    getMouseCoors(&mouse_left_2[0], &mouse_left_2[1]);

                mouse_left_write_1 = !mouse_left_write_1;
                
                break;

            case SDL_BUTTON_RIGHT:
                if (mouse_right_write_1)
                    getMouseCoors(&mouse_right_1[0], &mouse_right_1[1]);
                else
                    getMouseCoors(&mouse_right_2[0], &mouse_right_2[1]);

                mouse_right_write_1 = !mouse_right_write_1;

                break;
            }
            break;
        
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                mouse_left_write_1 = true;
                mouse_left_1[0] = -1;
                break;

            case SDL_BUTTON_RIGHT:
                mouse_right_write_1 = true;
                mouse_right_1[0] = -1;
                break;
            }
            break;
        }
    }


    //put white node
    if (mouse_left_1[0] != -1)
    {
        if (mouse_left_write_1)
        {
            getMouseCoors(&mouse_left_1[0], &mouse_left_1[1]);
            drawLineOnNodes(mouse_left_2, mouse_left_1, 1);
        }
        else
        {
            getMouseCoors(&mouse_left_2[0], &mouse_left_2[1]);
            drawLineOnNodes(mouse_left_1, mouse_left_2, 1);
        }

        mouse_left_write_1 = !mouse_left_write_1;
    }
    

    if (mouse_right_1[0] != -1)
    {
        if (mouse_right_write_1)
        {
            getMouseCoors(&mouse_right_1[0], &mouse_right_1[1]);
            drawLineOnNodes(mouse_right_2, mouse_right_1, 0);
        }
        else
        {
            getMouseCoors(&mouse_right_2[0], &mouse_right_2[1]);
            drawLineOnNodes(mouse_right_1, mouse_right_2, 0);
        }

        mouse_right_write_1 = !mouse_right_write_1;
    }
}

void Application::update() {}

void Application::renderGrid()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //render stuff
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);

    for (int x = 0; x < windowWidth; x += nodeSize + gapSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    }

    for (int y = 0; y < windowHeight; y += nodeSize + gapSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
    }
    ////
}

void Application::render()
{
    if (screenChanged)
    {
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        Application::renderGrid();

        for(int y = 0; y < map->getHeight(); ++y)
        {
            for(int x = 0; x < map->getWidth(); ++x)
            {
                Node* node = map->get(x, y);
                if (node->open) //open node
                {
                    colorNode(x, y, "blue");
                }
                else if (node->closed) //closed node
                {
                    colorNode(x, y, "red");
                }
                else if (node->dValue == 1)
                {
                    colorNode(x, y, "white");
                }
            }
        }


        if (startNode)
            colorNode(startNode->x, startNode->y, "green");
        if (endNode)
            colorNode(endNode->x, endNode->y, "yellow");


        //RENDER PATH
        Node* currNode = graph->endNode;
        if (graph->pathFound)
        {
            while (currNode != graph->startNode)
            {
                colorNode(currNode->x, currNode->y, "green");
                currNode = currNode->parentNode;
            }
            colorNode(currNode->x, currNode->y, "green");
        }


        SDL_RenderPresent(renderer);
        screenChanged = false;
    }
}

void Application::colorNode(int x, int y, std::string color)
{
    x = x * nodeSize + (x + 1) * gapSize;
    y = y * nodeSize + (y + 1) * gapSize;
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = nodeSize;
    rect.h = nodeSize;

    if (color == "white")
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    else if (color == "black")
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    else if (color == "green")
        SDL_SetRenderDrawColor(renderer, 52, 235, 52, 255);
    else if (color == "red")
        SDL_SetRenderDrawColor(renderer, 235, 52, 52, 255);
    else if (color == "blue")
        SDL_SetRenderDrawColor(renderer, 52, 52, 235, 255);
    else if (color == "yellow")
        SDL_SetRenderDrawColor(renderer, 255, 187, 0, 255);

    SDL_RenderFillRect(renderer, &rect);

}


void Application::findPath()
{
    if (startNode && endNode)
    {
        graph->findPath(startNode, endNode);

        screenChanged = true;
    }
}


void Application::clearScreen()
{
    //clear map
    for (int y = 0; y < map->getHeight(); y++)
    {
       for (int x = 0; x < map->getWidth(); x++)
        {
            map->get(x, y)->dValue = 0;
        } 
    }

    //
    startNode = nullptr;
    endNode = nullptr;

    graph->cleanUp();


    screenChanged = true;
}



void Application::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Application closed.\n";

    delete graph, map;
    delete this;
}

bool Application::running()
{
    return isRunning;
}

bool Application::escPressed()
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) )
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            return true;
            break;

        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
            case SDLK_ESCAPE:
                return true;
                break;
            }
        }
    }

    return false;
}

void Application::getMouseCoors(int* x, int* y)
{
    SDL_GetMouseState(x, y);
    *x = div(*x, nodeSize + gapSize).quot;
    *y = div(*y, nodeSize + gapSize).quot;
}

void Application::changeNodeOnMap(int x, int y, char value)
{
    if (x < map->getWidth() && y < map->getHeight())
    {
        map->get(x, y)->dValue = value;
    }
}

void Application::drawLineOnNodes(int from[], int to[], char putOrRemove)
{
    //The reason this function looks incredibly ugly is that I stole it. :c

    int x,y,dx,dy,dfrom[2],px,py,xe,ye,i;
    dx=to[0]-from[0];
    dy=to[1]-from[1];
    dfrom[0]=fabs(dx);
    dfrom[1]=fabs(dy);
    px=2*dfrom[1]-dfrom[0];
    py=2*dfrom[0]-dfrom[1];
    if(dfrom[1]<=dfrom[0])
    {
     if(dx>=0)
     {
      x=from[0];
      y=from[1];
      xe=to[0];
     }
     else
     {
      x=to[0];
      y=to[1];
      xe=from[0];
     }
     
     changeNodeOnMap(x, y, putOrRemove);
     
     for(i=0;x<xe;i++)
     {
      x=x+1;
      if(px<0) //
      {
       px=px+2*dfrom[1];
      }
      else
      {
       if((dx<0 && dy<0) || (dx>0 && dy>0))
       {
        y=y+1;
       }
       else
       {
        y=y-1;
       }
       px=px+2*(dfrom[1]-dfrom[0]);
      }

     changeNodeOnMap(x, y, putOrRemove);

     }
    }
    else
    {
     if(dy>=0)
     {
      x=from[0];
      y=from[1];
      ye=to[1];
     }
     else
     {
      x=to[0];
      y=to[1];
      ye=from[1];
     }

     changeNodeOnMap(x, y, putOrRemove);

     for(i=0;y<ye;i++)
     {
      y=y+1;
      if(py<=0)
      {
       py=py+2*dfrom[0];
      }
      else
      {
       if((dx<0 && dy<0) || (dx>0 && dy>0))
       {
        x=x+1;
       }
       else
       {
        x=x-1;
       }
       py=py+2*(dfrom[0]-dfrom[1]);
      }
      
     changeNodeOnMap(x, y, putOrRemove);

     }
    }

    screenChanged = true;
}


