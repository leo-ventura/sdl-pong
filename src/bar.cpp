#include <iostream>
#include <string>
#include "bar.h"

Bar::Bar(int x = 0, int y = 0, int w = 0, int h = 0, SDL_Surface *surf = NULL) {
  this->x = x;
  this->y = y;
  this->stepY = 0;
  this->w = w;
  this->h = h;
  this->surf = surf;
}

void Bar::setBar(int x, int y, int w, int h, SDL_Surface *surf) {
  this->x = x;
  this->y = y;
  this->stepY = stepY;
  this->w = w;
  this->h = h;
  this->surf = surf;
}

void Bar::setStepY(int stpY) {this->stepY = stpY;}

int Bar::getX() {return x;}

int Bar::getY() {return y;}

int Bar::getStepY() {return stepY;}

int Bar::getW() {return w;}

int Bar::getH() {return h;}

SDL_Surface* Bar::getSurf() {return surf;}

void Bar::move(int h, int bh) {
  this->y += stepY;

  if (y < 0 || y > h - bh)
    stepY = 0;
}
