#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "structs.h"

Game game;
Sprite sprite[MAX_SPRITES];

DECLSPEC SDL_Surface *SDLCALL IMG_Load(const char *file);

#endif /* GRAPHICS_H */
