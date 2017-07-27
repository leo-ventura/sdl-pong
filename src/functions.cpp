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
#include "ball.h"
#include "ball.cpp"

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

  gBarSurface = getMedia("../images/bar.png");
  gBallSurface = getMedia("../images/ball.png");

  if (!gBarSurface || !gBallSurface) {
    cout << "Could not load media! Error: " << SDL_GetError() << endl;
    return false;
  }

  return true;
}

void closeAll() {

  SDL_FreeSurface(gScreenSurface);
  SDL_FreeSurface(gBarSurface);
  SDL_FreeSurface(gBallSurface);
  gScreenSurface = NULL;
  gBarSurface = NULL;
  gBallSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  TTF_CloseFont(gFont);
  gFont = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void loadFont(int size) {
  gFont = TTF_OpenFont("../images/alagard_BitFont.ttf", size);
  if (!gFont) {
    cout << "Failed to load font! Error: " << TTF_GetError() << endl;
    gQuit = true;
  }
  if(_DEBUG) cout << "[Loaded font]" << endl;
}

SDL_Surface* loadText(string text, SDL_Color color) {

  SDL_Surface *optimizedTextSurface;

  SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);

  if (!textSurface) {
    cout << "Unable to render text. Error: " << TTF_GetError() << endl;
    gQuit = true;
  }

  optimizedTextSurface = SDL_ConvertSurface(textSurface, gScreenSurface->format, 0);
  if (!optimizedTextSurface) {
    cout << "Unable to create texture. Error: " << TTF_GetError() << endl;
    gQuit = true;
  }
  SDL_FreeSurface(textSurface);

  return optimizedTextSurface;
}

void putDimensions(SDL_Rect* src, int srcw, int srch, SDL_Rect* dst, int dstx, int dsty) {
  src->x = 0;
  src->y = 0;
  src->w = srcw;
  src->h = srch;
  dst->x = dstx;
  dst->y = dsty;
}

/*void collision(Bar *bar, Ball *ball) {
  if(_DEBUG)
    cout << "[entered collision]" << endl;

  if(_DEBUG)
    cout << "[bar->getX() is giving me " << bar->getX() << "]" << endl;

  if(bar->getX() + BAR_WIDTH < ball->getX()
  && bar->getX() > ball->getX()
  && bar->getY() > ball->getY()
  && bar->getY() + BAR_HEIGHT < ball->getY()) {
    if(_DEBUG)
      cout << "[has collided]" << endl;
    ball->setStepX(-ball->getStepX());
  }
}*/

void startGame() {

  // event handler
  SDL_Event e;

  // bar's source and distance
  SDL_Rect srcLeftBar, dstLeftBar;
  SDL_Rect srcRightBar, dstRightBar;

  // ball's source and distance
  SDL_Rect srcBall, dstBall;

  // declaring left bar, right bar and ball
  Bar leftBar(30, WINDOW_HEIGHT/2, BAR_WIDTH, BAR_HEIGHT, gBarSurface);
  Bar rightBar(WINDOW_WIDTH - BAR_WIDTH - 30, WINDOW_HEIGHT/2, BAR_WIDTH, BAR_HEIGHT, gBarSurface);
  Ball ball(WINDOW_WIDTH/2 - BALL_WIDTH/2, WINDOW_HEIGHT/2 - BALL_HEIGHT/2, BALL_WIDTH, BALL_HEIGHT, gBallSurface);

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
          else if (e.key.keysym.sym == SDLK_SPACE) {
            srand(time(NULL));
            if(rand()%2) {
              ball.setStepX(2);
              rand()%2 ? ball.setStepY(1):ball.setStepY(-1);
            } else {
              ball.setStepX(-2);
              rand()%2 ? ball.setStepY(1):ball.setStepY(-1);
            }
          }
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
    ball.move(BALL_HEIGHT, BALL_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH);

    ball.collision(leftBar.getX(), leftBar.getY());
    ball.collision(rightBar.getX(), rightBar.getY());
    //leftBar.collision(ball.getX(), ball.getY());
    //rightBar.collision(ball.getX(), ball.getY());

    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    // putDimensions prototype
    // putDimensions(SDL_Rect* src, int srcx, int srcy, int srcw, int srch, SDL_Rect* dst, int dstx, int dsty);
    putDimensions(&srcLeftBar, BAR_WIDTH, BAR_HEIGHT, &dstLeftBar, leftBar.getX(), leftBar.getY());
    putDimensions(&srcRightBar, BAR_WIDTH, BAR_HEIGHT, &dstRightBar, rightBar.getX(), rightBar.getY());
    putDimensions(&srcBall, BALL_WIDTH, BALL_HEIGHT, &dstBall, ball.getX(), ball.getY());

    if(SDL_BlitSurface(leftBar.getSurf(), &srcLeftBar, gScreenSurface, &dstLeftBar) < 0
    || SDL_BlitSurface(rightBar.getSurf(), &srcRightBar, gScreenSurface, &dstRightBar) < 0
    || SDL_BlitSurface(ball.getSurf(), &srcBall, gScreenSurface, &dstBall) < 0) {
      cout << "SDL could not blit! SDL Error: " << SDL_GetError() << endl;
      gQuit = true;
    }

    SDL_Delay(5);
    SDL_UpdateWindowSurface(gWindow);
  }
}

void menu() {
  unsigned int cursor = 0;
  SDL_Event e;
  SDL_Surface *start, *help, *exitGame;
  SDL_Rect dstStart, srcStart, dstHelp, srcHelp, dstExit, srcExit;
  SDL_Color color = {255, 255, 255};

  if(_DEBUG)
    cout << "[Menu opened]" << endl;

  loadFont(50);

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
          } else if(e.key.keysym.sym == SDLK_ESCAPE) {
            if(_DEBUG)
              cout << "[esc pressed]" << endl;
            gQuit = true;
          } else if (e.key.keysym.sym == SDLK_DOWN) {
            cursor = (cursor + 1)%3;
            if (_DEBUG) cout << "[Cursor is at pos " << cursor << "]" << endl;
          } else if (e.key.keysym.sym == SDLK_UP) {
            cursor = (cursor + 2)%3;
            if (_DEBUG) cout << "[Cursor is at pos " << cursor << "]" << endl;
          }
          break;
      }
    }

    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));

    // putDimensions(SDL_Rect* src, int srcw, int srch, SDL_Rect* dst, int dstx, int dsty)
    putDimensions(&srcStart, 200, 75, &dstStart, WINDOW_WIDTH/2-75, 150);
    putDimensions(&srcHelp, 200, 75, &dstHelp, WINDOW_WIDTH/2-75, 225);
    putDimensions(&srcExit, 200, 75, &dstExit, WINDOW_WIDTH/2-75, 300);

    start = loadText("Start", color);
    help = loadText("Help", color);
    exitGame = loadText("Exit", color);

    if(SDL_BlitSurface(start, &srcStart, gScreenSurface, &dstStart) < 0
    || SDL_BlitSurface(help, &srcHelp, gScreenSurface, &dstHelp) < 0
    || SDL_BlitSurface(exitGame, &srcExit, gScreenSurface, &dstExit) < 0) {
      cout << "SDL could not blit! SDL Error: " << SDL_GetError() << endl;
      gQuit = true;
    }

    SDL_UpdateWindowSurface(gWindow);
  }
}
