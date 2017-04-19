#ifndef REDEFINE_H
# define REDEFINE_H

# include "structs.h"

t_control control;
t_redefine redefine;

void flushInputs(void);

int getSingleInput(void);

void drawString(t_game*, char *, int, int, TTF_Font *, int, int);

void drawRedefine(t_game *);

void drawBackground(t_game *, int);

#endif /* REDEFINE_H */
