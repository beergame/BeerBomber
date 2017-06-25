#ifndef REDEFINE_H
# define REDEFINE_H

# include "structs.h"

void flush_inputs(void);

int get_single_input(void);

void draw_string(t_game*, char *, int, int, TTF_Font *, int, int);

void draw_redefine(t_game *);

void draw_background(t_game *, int);

#endif /* REDEFINE_H */
