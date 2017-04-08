#ifndef BOMB_H
# define BOMB_H

# include "structs.h"

void drawImage(Game *, SDL_Texture *, int, int);

SDL_Texture *getSprite(int);

Entity *addFire(MapCase **, int, int);

#endif /* BOMB_H */
