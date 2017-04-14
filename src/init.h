#ifndef INIT_H
# define INIT_H

# include "structs.h"

void freeSprites(void);

void freeMap(MapCase **);

void closeFont(TTF_Font *);

TTF_Font *loadFont(char *, int);

#endif /* INIT_H */
