#ifndef DRAW_H
# define DRAW_H

# include "structs.h"

Game game;

void drawMap(MapCase **map);

void drawEntities(MapCase **map);

void drawString(char *, int, int, TTF_Font *, int, int);

#endif /* DRAW_H */

