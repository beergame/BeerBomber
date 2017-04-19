#ifndef __MAIN_H__
# define __MAIN_H__

# include "structs.h"

void init_main(t_game *);

void cleanup(t_game *);

int is_new_game(t_game *, int *);

int getInput(t_game *);

void draw(t_game *);

void loadAllSprites(t_game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int do_redefine(t_game *);

void client_beer_bomber(t_game *);

void *server_beer_bomber();

#endif /* __MAIN_H__ */
