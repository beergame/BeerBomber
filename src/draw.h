#ifndef DRAW_H
# define DRAW_H

# include "structs.h"

void draw_map_base(t_game *);

void draw_map_entity(t_game *);

void draw_player(t_game *);

void draw_string(t_game *, char *, int, int, TTF_Font *, int, int);

void draw_log_string(t_game *, char *, int, int, TTF_Font *);

void draw_background(t_game *, int);

#endif /* DRAW_H */

