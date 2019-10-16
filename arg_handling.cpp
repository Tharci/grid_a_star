#include "arg_handling.h"
#include <string>


//-h: height
//-w: width
//fullscr: fullscreen
//-d: animation delay
//-n: node size




extern bool fullscr = false; //not supported yet
extern int animDelay = 0;
extern int window_height = 600;
extern int window_width = 800;
extern int nodeSize = 15;
extern int fps = 30;
extern int  refreshRate = 20;


void argHandling(int argc, const char* argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string arg(argv[i]);

            if (arg == "fullscr")
            {
                fullscr = true;
            }

            if (arg.substr(0, 2) == "-d")
            {
                animDelay = std::stoi(arg.substr(2, arg.size()-2));
            }

            if (arg.substr(0, 2) == "-w")
            {
                try
                {
                    window_width = std::stoi(arg.substr(2, arg.size()-2));
                }
                catch(const std::exception& e) {}
            }

            if (arg.substr(0, 2) == "-h")
            {
                try
                {
                    window_height = std::stoi(arg.substr(2, arg.size()-2));
                }
                catch(const std::exception& e) {}
            }

            if (arg.substr(0, 2) == "-n")
            {
                try
                {
                    nodeSize = std::stoi(arg.substr(2, arg.size()-2));
                }
                catch(const std::exception& e) {}
            }

            if (arg.substr(0, 2) == "-f")
            {
                try
                {
                    fps = std::stoi(arg.substr(2, arg.size()-2));
                }
                catch(const std::exception& e) {}
            }

            if (arg.substr(0, 2) == "-r")
            {
                try
                {
                    refreshRate = std::stoi(arg.substr(2, arg.size()-2));
                }
                catch(const std::exception& e) {}
            }
        }
    }
}