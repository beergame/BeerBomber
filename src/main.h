#ifndef MAIN_H
# define MAIN_H

# include "structs.h"

Control customControl, input;
Sprite sprite[MAX_SPRITES];
Redefine redefine;

void initBeerBomber(Game *);

void cleanup(Game *);

int getInput(Game *);

void draw(Game *);

Entity *initPlayer(MapCase **, int, int);

void playerMove(MapCase **, Entity *);

void playerThrowBomb(MapCase **, Entity *);

void entitiesActions(MapCase **);

void loadAllSprites(Game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int doRedefine(Game *);

MapCase **loadMap();

void *clientBeerBomber(void *);

void *serverBeerBomber(void *);

#endif /* MAIN_H */
