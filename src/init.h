#ifndef INIT_H
# define INIT_H

# include "structs.h"

Game game;

void freeSprites(void);

void freeMap(MapCase **);

void closeFont(TTF_Font *);

#endif /* INIT_H */
