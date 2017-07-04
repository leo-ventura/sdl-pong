#include <iostream>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// functions forward declaration
int init();
int loadMedia();
SDL_Surface *getMedia(char*);
void closeAll();

// global variables forward declaration

using namespace std;

int main(int argc, char const *argv[]) {
  // starts SDL and load all medias
  if (!init() || !loadMedia()) {
    cout << "SDL could not initialize. Error: " << SDL_GetError() << endl;
  }
  gQuit = false;
  menu();
  closeAll();
  return 0;
}
