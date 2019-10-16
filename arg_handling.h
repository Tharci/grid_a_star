#ifndef ARG_HANDLING_H
#define ARG_HANDLING_H

#include <string>


extern bool fullscr;
extern int animDelay;
extern int window_height;
extern int window_width;
extern int nodeSize;
extern int fps;
extern int  refreshRate;

void argHandling(int argc, const char* argv[]);

#endif