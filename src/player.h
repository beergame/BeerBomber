#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

void drawImage(t_game *, SDL_Texture *, int, int);

t_entity *addBomb(t_map_case **, int, int);

SDL_Texture *getSprite(int);

#endif /* PLAYER_H */
