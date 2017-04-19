#ifndef __CLIENT_H__
# define __CLIENT_H__

# include "structs.h"

t_redefine redefine;

void initBeerBomber(t_game *);

void cleanup(t_game *);

int doConfig(t_game *);

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

char **my_str_to_wordtab(char *, char);

t_map **load_server_map();

#endif /* __CLIENT_H__ */
