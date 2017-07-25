#ifndef BALL_H
#define BALL_H

class Ball : public Bar {

private:
  int stepX;

public:
  Ball(int, int, int, int, SDL_Surface*);
  ~Ball();
  // function to set stepX
  void setStepX(int);

  // function to get stepX
  int getStepX();

  // other functions
  void move(int, int, int, int);
};

#endif
