#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "global.h"

bool gQuit = false;
SDL_Surface *gScreenSurface = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface* gBarSurface = NULL;
SDL_Surface *gBallSurface = NULL;
TTF_Font *gFont = NULL;
