#ifndef __MAIN_H__
# define __MAIN_H__

# include "structs.h"

int init_main(t_game *);

void cleanup(t_game *);

void is_new_game(t_game *, int *);

void choose_nb_player(t_game *, int *);

int get_input(t_game *);

void draw(t_game *);

void load_all_sprites(t_game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int do_redefine(t_game *);

void client_beer_bomber(t_game *);

void *server_beer_bomber(void *);

#endif /* __MAIN_H__ */
