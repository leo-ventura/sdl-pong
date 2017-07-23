#ifndef BAR_H
#define BAR_H

class Bar {

private:
  int x, y;
  int stepY;
  int w, h;
  SDL_Surface *surf;

public:
  Bar(int, int, int, int, SDL_Surface*);
  ~Bar() {}

  // set functions
  void setBar(int, int, int, int, SDL_Surface*);
  void setStepY(int);

  // get functions
  int getX();
  int getY();
  int getStepY();
  int getW();
  int getH();
  SDL_Surface* getSurf();

  // other functions
  void move(int, int);
};

#endif
