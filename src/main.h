#ifndef MAIN_H
# define MAIN_H

# include "structs.h"

Control customControl, input;
Sprite sprite[MAX_SPRITES];
Redefine redefine;

void init(char *, Game *);

void cleanup(Game *);

int getInput(Game *);

void draw(Game *);

Entity *initPlayer(MapCase **, int, int);

void playerMove(MapCase **, Entity *);

void playerThrowBomb(MapCase **, Entity *);

void entitiesActions(MapCase **);

void loadAllSprites(Game *);

void doCollisions(void);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int doRedefine(Game *);

MapCase **loadMap();

void drawMap(MapCase **);

#endif /* MAIN_H */
