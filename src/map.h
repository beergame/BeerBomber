#ifndef MAP_H
# define MAP_H

#include "structs.h"

void draw_image(t_game *, SDL_Texture *, int, int, double);

void draw_player_image(t_game *game, SDL_Texture *image, int x, int y);

SDL_Texture *get_sprite(int);

#endif /* MAP_H */
