#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool init();
SDL_Surface* getMedia(std::string);
bool loadMedia();
void closeAll();
SDL_Surface* loadText(TTF_Font, std::string, SDL_Color);
void putDimensions(SDL_Rect*, int, int, int, int, SDL_Rect*, int, int);
void startGame();
void menu();

#endif
