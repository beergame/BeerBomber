#ifndef __CONFIG_H__
# define __CONFIG_H__

# include "structs.h"

void flushInputs(void);

int getSingleInput(void);

void drawString(Game*, char *, int, int, TTF_Font *, int, int);

void drawRedefine(Game *);

void drawBackground(Game *, int);

void drawConfig(Game *);

void drawBtn(Game *);

#endif /* __CONFIG_H__ */
