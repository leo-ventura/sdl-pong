#include <iostream>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "functions.h"
#include "global.h"
#include "bar.h"

using namespace std;

int main(int argc, char const *argv[]) {
  // starts SDL and load all medias
  if (!init() || !loadMedia()) {
    cout << "SDL could not initialize. Error: " << SDL_GetError() << endl;
    return 1;
  }
  menu();
  closeAll();
  return 0;
}
