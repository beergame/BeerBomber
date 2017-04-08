#ifndef DRAW_H
# define DRAW_H

# include "structs.h"

void drawMap(Game *, MapCase **map);

void drawEntities(Game *, MapCase **map);

void drawString(Game *, char *, int, int, TTF_Font *, int, int);

#endif /* DRAW_H */

