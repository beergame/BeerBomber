#ifndef MAP_H
# define MAP_H

#include "structs.h"

void drawImage(t_game *, SDL_Texture *, int, int);

SDL_Texture *getSprite(int);

t_entity *addBush();

#endif /* MAP_H */
