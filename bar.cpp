#include <iostream>
#include "bar.h"

Bar::Bar(int x, int y, int w, int h, SDL_Surface *surf) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->surf = surf;
}
