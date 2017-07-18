#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef BAR_H
#define BAR_H

class Bar {

private:
  int x, y;
  int stepX, stepY;
  int w, h;
  SDL_Surface *surf;

public:
  Bar(int, int, int, int, SDL_Surface*);
  ~Bar() {}

  // set functions
  void setBar(int, int, int, int, SDL_Surface*);

  // get functions
  int getX();
  int getY();
  int getStepX();
  int getStepY();
  int getW();
  int getH();
  SDL_Surface* getSurf();
};

#endif
