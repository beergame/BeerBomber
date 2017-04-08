#ifndef REDEFINE_H
# define REDEFINE_H

# include "structs.h"

Control customControl;
Redefine redefine;

void flushInputs(void);

int getSingleInput(void);

void drawString(Game*, char *, int, int, TTF_Font *, int, int);

void drawRedefine(Game *);

#endif /* REDEFINE_H */
