#ifndef INIT_H
# define INIT_H

# include "structs.h"

void freeSprites(void);

void free_map(t_map **);

void closeFont(TTF_Font *);

TTF_Font *loadFont(char *, int);

t_map **load_server_map();

#endif /* INIT_H */
