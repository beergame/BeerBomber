#ifndef INIT_H
# define INIT_H

# include "structs.h"

TTF_Font *loadFont(char *, int);

t_map **load_map();

void load_all_sprites(t_game *);

void load_all_sound(t_game *);

#endif /* INIT_H */
