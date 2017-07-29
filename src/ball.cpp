#include <iostream>
#include <string>
#include "ball.h"

Ball::Ball(int x = 0, int y = 0, int w = 0, int h = 0, SDL_Surface *surf = NULL) {
  this->x = x;
  this->y = y;
  this->stepX = 0;
  this->stepY = 0;
  this->w = w;
  this->h = h;
  this->surf = surf;
}

void Ball::setStepX(int sx) {stepX = sx;}

void Ball::setStepY(int stpY) {stepY = stpY;}

int Ball::getX() {return x;}

int Ball::getY() {return y;}

int Ball::getStepX() {return stepX;}

int Ball::getStepY() {return stepY;}

int Ball::getW() {return w;}

int Ball::getH() {return h;}

SDL_Surface* Ball::getSurf() {return surf;}

void Ball::move(int ballh, int ballw, int screenh, int screenw) {
  this->x += stepX;
  this->y += stepY;

  if(x < 0 || x > screenw - ballw)
    this->stepX *= -1;

  if(y < 0 || y > screenh - ballh)
    this->stepY *= -1;
}

void Ball::collision(int barx, int bary) {

  if(this->x < barx + BAR_WIDTH
  && this->x > barx
  && this->y > bary
  && this->y < bary + BAR_HEIGHT) {
    this->stepX *= -1;
  }
}
