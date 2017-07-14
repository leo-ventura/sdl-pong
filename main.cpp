#include <iostream>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "functions.h"
#include "global.h"

// I'm not sure if this is the right way of declaring functions and variables in C++ but I'm trying to figure it out

// declaring functions
bool init();
SDL_Surface* getMedia(string pwd);
bool loadMedia();
void closeAll();

// declaring variables
bool gQuit = false;
SDL_Surface *gScreenSurface = NULL;
SDL_Window *gWindow = NULL;


using namespace std;

int main(int argc, char const *argv[]) {
  // starts SDL and load all medias
  if (!init() || !loadMedia()) {
    cout << "SDL could not initialize. Error: " << SDL_GetError() << endl;
    return 1;
  }
  gQuit = false;
  menu();
  closeAll();
  return 0;
}
