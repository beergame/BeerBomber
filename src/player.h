#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

Control input;

void drawImage(Game *, SDL_Texture *, int, int);

Entity *addBomb(MapCase **, int, int);

SDL_Texture *getSprite(int);

#endif /* PLAYER_H */
