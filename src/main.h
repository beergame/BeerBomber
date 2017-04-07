#ifndef MAIN_H
# define MAIN_H

# include "structs.h"

Game game;
Control customControl, input;
Sprite sprite[MAX_SPRITES];
Redefine redefine;

void init(char *);

void cleanup(void);

void getInput(void);

void draw(void);

Entity *initPlayer(MapCase **, int, int);

void playerMove(MapCase **, Entity *);

void playerThrowBomb(MapCase **, Entity *);

void entitiesActions(MapCase **);

void loadAllSprites(void);

void doCollisions(void);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

void doRedefine(void);

MapCase **loadMap();

void drawMap(MapCase **);

#endif /* MAIN_H */
