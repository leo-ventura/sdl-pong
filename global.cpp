#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "global.h"

// initialize global variables here
bool gQuit = false;
SDL_Texture *gTexture = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
