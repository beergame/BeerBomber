#ifndef REDEFINE_H
# define REDEFINE_H

# include "structs.h"

Entity entity[MAX_ENTITIES];
Entity player;
Game game;
Entity *self;
Control customControl;
Redefine redefine;

void flushInputs(void);

int getSingleInput(void);

void drawString(char *, int, int, TTF_Font *, int, int);

void drawRedefine(void);

#endif /* REDEFINE_H */
