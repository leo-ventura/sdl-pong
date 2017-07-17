#ifndef BAR_H
#define BAR_H

class Bar {
private:
  int x, y;
  int w, h;
  SDL_Surface *surf;
public:
  Bar::Bar(int x, int y, int w, int h, SDL_Surface *surf);
  ~Bar() {}
};

#endif
