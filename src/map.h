#ifndef MAP_H
# define MAP_H

#include "structs.h"

void drawImage(Game *, SDL_Texture *, int, int);

SDL_Texture *getSprite(int);

Entity *addBush();

#endif /* MAP_H */
