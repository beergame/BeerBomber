#ifndef __CLIENT_H__
# define __CLIENT_H__

# include "structs.h"

void init_main(t_game *);

void cleanup(t_game *);

int getInput(t_game *);

void draw(t_game *);

void loadAllSprites(t_game *);

TTF_Font *loadFont(char *, int);

void delay(unsigned int);

int do_redefine(t_game *);

char **my_str_to_wordtab(char *, char);

t_map **load_map();

void init_client(t_game *);

#endif /* __CLIENT_H__ */
