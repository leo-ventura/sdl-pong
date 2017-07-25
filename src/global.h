#ifndef GLOBAL_H
#define GLOBAL_H

#define _DEBUG true
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 660
#define BAR_WIDTH 30
#define BAR_HEIGHT 100
#define BALL_WIDTH 15
#define BALL_HEIGHT 15

extern bool gQuit;
extern SDL_Surface *gScreenSurface;
extern SDL_Window *gWindow;
extern SDL_Surface *gBarSurface;
extern SDL_Surface *gBallSurface;

#endif
