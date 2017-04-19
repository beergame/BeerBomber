#ifndef BOMB_H
# define BOMB_H

# include "structs.h"

void drawImage(t_game *, SDL_Texture *, int, int);

SDL_Texture *getSprite(int);

t_entity *addFire(t_map_case **, int, int);

#endif /* BOMB_H */
