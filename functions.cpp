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

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if(!gRenderer) {
    cout << "Renderer could not be created! Error: " << SDL_GetError() << endl;
  }

  // initializes renderer color
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError());
    return false;
  }
  gScreenSurface = SDL_GetWindowSurface(gWindow);
  return true;
}

SDL_Surface *getTexture(string pwd) {
  SDL_Texture* newTexture = NULL;

  SDL_Surface *loadedSurface = IMG_Load(pwd);

  if(!loadedSurface) {
    cout << "Unable to load image! SDL_image Error: " << IMG_GetError() << endl;
    gQuit = true;
  }

  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  if (!newTexture) {
    cout << "Unable to create texture! Error: " << SDL_GetError() << endl;
    gQuit = true;
  }
  SDL_FreeSurface(loadedSurface);
  return newTexture;
}

bool loadMedia() {
  gBarSurface = getTexture("./images/bar.png");
  gBallSurface = getTexture("./images/ball.png");

  if (!gBarSurface || !gBallSurface) {
    cout << "Could not load media! Error: " << SDL_GetError() << endl;
    return false;
  }
  return true;
}

void closeAll() {

  SDL_DestroyTexture(gTexture);
  gTexture = NULL;

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gRenderer = NULL;
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}

void startGame() {
  SDL_Event e;

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
    // fills the screen with the color set by SDL_SetRenderDrawColor
    SDL_RenderClear(gRenderer);

    // now we render the texture to the screen
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

    // update screen/window (since we're using render, there's no SDL_UpdateWindowSurface)
    SDL_RenderPresent(gRenderer);
  }
}
