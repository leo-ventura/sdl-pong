#include <iostream>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "functions.h"

using namespace std;

bool init() {
  if (TTF_Init() < 0 || SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL unable to initialize! Error: " << SDL_GetError();
    return false;
  }

  gWindow = SDL_CreateWindow("Hey! Enjoy your little Pong!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(gWindow == NULL) {
    cout << "Window could not be created! SDL Error: " << SDL_GetError();
    return false;
  }

  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError());
    return false;
  }
  gScreenSurface = SDL_GetWindowSurface(gWindow);
  return true;
}

SDL_Surface *getMedia(string pwd) {
  SDL_Surface *optimizedSurface = NULL;

  SDL_Surface *loadedSurface = IMG_Load(pwd);

  if(loadedSurface == NULL) {
    cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << endl;
    gQuit = true;
  }

  optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
  if(optimizedSurface == NULL) {
    cout << "Unable to optimize image! SDL Error: " << SDL_GetError() << endl;
    gQuit = true;
  }

  SDL_FreeSurface(loadedSurface);

  return optimizedSurface;
}

bool loadMedia() {
  gBarSurface = getMedia("./images/bar.png");
  gBallSurface = getMedia("./images/ball.png");

  if (!gBarSurface || !gBallSurface) {
    cout << "Could not load media! Error: " << SDL_GetError() << endl;
    return false;
  }
  return true;
}

void closeAll() {

  SDL_FreeSurface(gScreenSurface);
  gScreenSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
}

void menu() {
  int cursor = 0;
  SDL_Event e;

  while(!gQuit) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
        case SDL_QUIT:
          gQuit = true;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_RETURN) {
            switch(cursor) {
              case 0:
                startGame();
                break;
              case 1:
                help();
                break;
              case 2:
                gQuit = true;
                break;
            }
          }
          // lots of things to add here
          break;
      }
    }
  }
}
