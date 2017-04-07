#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

Control input;

void drawImage(SDL_Surface *, int, int);

Entity *addBomb(MapCase **, int, int);

SDL_Surface *getSprite(int);

#endif /* PLAYER_H */
