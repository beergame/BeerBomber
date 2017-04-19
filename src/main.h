#ifndef MAIN_H
# define MAIN_H

# include "structs.h"

//t_sprite sprite[MAX_SPRITES];
t_redefine redefine;

void initBeerBomber(t_game *);

void cleanup(t_game *);

int is_new_game(t_game *);

int getInput(t_game *);

void draw(t_game *);

t_entity *initPlayer(t_map_case **, int, int);

void playerMove(t_game *, t_map_case **, t_entity *);

void playerThrowBomb(t_game *, t_map_case **, t_entity *);

void entitiesActions(t_map_case **);

void loadAllSprites(t_game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int doRedefine(t_game *);

t_map_case **load_map();

void client_beer_bomber(t_game *);

void *server_beer_bomber();

#endif /* MAIN_H */
