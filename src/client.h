#ifndef __CLIENT_H__
# define __CLIENT_H__

# include "structs.h"

Control customControl, input;
Sprite sprite[MAX_SPRITES];
Redefine redefine;

void initBeerBomber(Game *);

void cleanup(Game *);

int doConfig(Game *);

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

#endif /* __CLIENT_H__ */
