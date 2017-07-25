#include <iostream>
#include <string>
#include "ball.h"

void Ball::setStepX(int sx) {stepX = sx;}

int Ball::getStepX() {return stepX;}

void Ball::move(int ballh, int ballw, int screenh, int screenw) {
  this->x += stepX;
  this->y += stepY;

  if(y < 0 || y > screenh - ballh
  && x < 0 || x > screenw - ballw)
    stepY = 0;
}
