#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

void drawImage(t_game *, SDL_Texture *, int, int);

SDL_Texture *getSprite(int);

#endif /* PLAYER_H */
