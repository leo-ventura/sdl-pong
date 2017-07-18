#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // don't know why I have to include here
#ifndef GLOBAL_H
#define GLOBAL_H

#define _DEBUG true
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 600
#define BAR_WIDTH 30
#define BAR_HEIGHT 100

extern bool gQuit;
extern SDL_Surface *gScreenSurface;
extern SDL_Window *gWindow;
extern SDL_Surface *gBarSurface;

#endif
