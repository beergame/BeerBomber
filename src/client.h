#ifndef __CLIENT_H__
# define __CLIENT_H__

# include "structs.h"

int init_main(t_game *);

void clean_client(t_game *);

int get_input(t_game *);

void draw(t_game *);

void draw_wait_for_player(t_game *);

void draw_winner(t_game *);

void load_all_sprites(t_game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int do_redefine(t_game *);

char **my_str_to_wordtab(char *, char);

t_map **load_map();

void init_client(t_game *);

int send_serialize_request(t_request *, int);

#endif /* __CLIENT_H__ */
