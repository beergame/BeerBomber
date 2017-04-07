#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "structs.h"

Sprite sprite[MAX_SPRITES];
Game game;

DECLSPEC SDL_Surface *SDLCALL IMG_Load(const char *file);

#endif /* GRAPHICS_H */
