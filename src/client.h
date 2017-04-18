#ifndef __CLIENT_H__
# define __CLIENT_H__

# include "structs.h"

//Sprite sprite[MAX_SPRITES];
Redefine redefine;

void initBeerBomber(Game *);

void cleanup(Game *);

int doConfig(Game *);

int getInput(Game *);

void draw(Game *);

Entity *initPlayer(MapCase **, int, int);

void playerMove(Game *, MapCase **, Entity *);

void playerThrowBomb(Game *, MapCase **, Entity *);

void entitiesActions(MapCase **);

void loadAllSprites(Game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int doRedefine(Game *);

MapCase **loadMap();

char **my_str_to_wordtab(char *, char);

t_map **load_server_map();

#endif /* __CLIENT_H__ */
