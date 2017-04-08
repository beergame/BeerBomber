#ifndef MAIN_H
# define MAIN_H

# include "structs.h"

Control customControl, input;
Sprite sprite[MAX_SPRITES];
Redefine redefine;

void init(char *, Game *);

void cleanup(Game *);

void getInput(Game *);

void draw(Game *);

Entity *initPlayer(MapCase **, int, int);

void playerMove(MapCase **, Entity *);

void playerThrowBomb(MapCase **, Entity *);

void entitiesActions(MapCase **);

void loadAllSprites(Game *);

void doCollisions(void);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

void doRedefine(Game *);

void loadMap(MapCase **);

void drawMap(MapCase **);

#endif /* MAIN_H */
