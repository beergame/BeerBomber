#ifndef DRAW_H
# define DRAW_H

# include "structs.h"

void draw_map(t_game *);

void drawEntities(t_game *, t_map_case **map);

void drawString(t_game *, char *, int, int, TTF_Font *, int, int);

void drawBackground(t_game *, int);

#endif /* DRAW_H */

