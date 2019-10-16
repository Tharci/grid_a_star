#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>

#include "application.h"
#include "arg_handling.h"


int main(int argc, const char* argv[])
{
    argHandling(argc, argv);

    Application* app = new Application();
    app->init("A star", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fullscr, window_width, window_height, nodeSize);


    while (app->running())
    {
        app->handleEvents();
        app->update();
        app->render();

        SDL_Delay(1000/fps);
    }

    app->clean();
  
    return 0;
}