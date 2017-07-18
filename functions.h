#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool init();
SDL_Surface* getMedia(std::string pwd);
bool loadMedia();
void closeAll();
void putDimensions(SDL_Rect*, int, int, int, int, SDL_Rect*, int, int);
void startGame();
void menu();

#endif
