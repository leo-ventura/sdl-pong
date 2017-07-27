#ifndef BALL_H
#define BALL_H

class Ball {

private:
  int x, y;
  int stepX, stepY;
  int w, h;
  SDL_Surface *surf;

public:
  Ball(int, int, int, int, SDL_Surface*);
  ~Ball() {}

  // functions to set stepX and stepY
  void setStepX(int);
  void setStepY(int);

  // get functions
  int getX();
  int getY();
  int getStepX();
  int getStepY();
  int getW();
  int getH();
  SDL_Surface* getSurf();

  // other functions
  void move(int, int, int, int);
  void collision(int, int);
};

#endif
