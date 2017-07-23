#include <iostream>
#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "functions.h"
#include "global.h"
#include "bar.cpp" // I don't know why it's not working including "bar.h"

using namespace std;

bool init() {

  if (TTF_Init() < 0 || SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL unable to initialize! Error: " << SDL_GetError();
    return false;
  }

  gWindow = SDL_CreateWindow("Hey! Enjoy your little Pong!",
  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(gWindow == NULL) {
    cout << "Window could not be created! SDL Error: " << SDL_GetError();
    return false;
  }

  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

  if(!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
    return false;
  }

  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

SDL_Surface *getMedia(string pwd) {

  SDL_Surface *optimizedSurface = NULL;

  SDL_Surface *loadedSurface = IMG_Load(pwd.c_str());

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
  // gBallSurface = getMedia("./images/ball.png");

  if (!gBarSurface /*|| !gBallSurface*/) {
    cout << "Could not load media! Error: " << SDL_GetError() << endl;
    return false;
  }

  return true;
}

void closeAll() {

  SDL_FreeSurface(gScreenSurface);
  SDL_FreeSurface(gBarSurface);
  //SDL_FreeSurface(gBallSurface);
  gScreenSurface = NULL;
  gBarSurface = NULL;
  //gBallSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}

void putDimensions(SDL_Rect* src, int srcx, int srcy, int srcw, int srch, SDL_Rect* dst, int dstx, int dsty) {
  src->x = srcx;
  src->y = srcy;
  src->w = srcw;
  src->h = srch;
  dst->x = dstx;
  dst->y = dsty;
}

void startGame() {

  // event handler
  SDL_Event e;

  // bar's source and distance
  SDL_Rect srcLeftBar, dstLeftBar;
  SDL_Rect srcRightBar, dstRightBar;

  // declaring left bar
  Bar leftBar(30, WINDOW_HEIGHT/2, BAR_WIDTH, BAR_HEIGHT, gBarSurface);
  Bar rightBar(WINDOW_WIDTH - BAR_WIDTH - 30, WINDOW_HEIGHT/2, BAR_WIDTH, BAR_HEIGHT, gBarSurface);

  // game loop
  while(!gQuit) {
    while (SDL_PollEvent(&e) != 0) {
      switch(e.type) {
        case SDL_QUIT:
          gQuit = true;
          break;
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_ESCAPE)
            gQuit = true;
          //else if (e.key.keysym.sym == SDLK_SPACE)
          else if (e.key.keysym.sym == SDLK_w)
            leftBar.setStepY(-1);
          else if (e.key.keysym.sym == SDLK_s)
            leftBar.setStepY(1);
          else if (e.key.keysym.sym == SDLK_UP)
            rightBar.setStepY(-1);
          else if (e.key.keysym.sym == SDLK_DOWN)
            rightBar.setStepY(1);
          break;
      }
    }

    leftBar.move(WINDOW_HEIGHT, BAR_HEIGHT);
    rightBar.move(WINDOW_HEIGHT, BAR_HEIGHT);

    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    // putDimensions prototype
    // putDimensions(SDL_Rect* src, int srcx, int srcy, int srcw, int srch, SDL_Rect* dst, int dstx, int dsty);
    putDimensions(&srcLeftBar, 0, 0, BAR_WIDTH, BAR_HEIGHT, &dstLeftBar, leftBar.getX(), leftBar.getY());
    putDimensions(&srcRightBar, 0, 0, BAR_WIDTH, BAR_HEIGHT, &dstRightBar, rightBar.getX(), rightBar.getY());

    if(SDL_BlitSurface(leftBar.getSurf(), &srcLeftBar, gScreenSurface, &dstLeftBar) < 0
    || SDL_BlitSurface(rightBar.getSurf(), &srcRightBar, gScreenSurface, &dstRightBar) < 0) {
      cout << "SDL could not blit! SDL Error: " << SDL_GetError() << endl;
      gQuit = true;
    }

    SDL_Delay(5);
    SDL_UpdateWindowSurface(gWindow);
  }
}

void menu() {
  int cursor = 0;
  SDL_Event e;

  if(_DEBUG)
    cout << "[Menu opened]" << endl;

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
                if (_DEBUG) cout << "[Started game]" << endl;
                startGame();
                break;
              case 1:
                if (_DEBUG) cout << "[Entered help]" << endl;
                //help();
                break;
              case 2:
                if (_DEBUG) cout << "[Exit]" << endl;
                gQuit = true;
                break;
            }
          }
          else if (e.key.keysym.sym == SDLK_DOWN) {
            cursor = (cursor + 1)%3;
            if (_DEBUG) cout << "[Cursor is at pos " << cursor << "]" << endl;

          } else if (e.key.keysym.sym == SDLK_UP) {
            cursor = (cursor + 2)%3;
            if (_DEBUG) cout << "[Cursor is at pos " << cursor << "]" << endl;
          }
          // lots of things to add here
          break;
      }
    }
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(gWindow);
  }
}
