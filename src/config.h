#ifndef __CONFIG_H__
# define __CONFIG_H__

# include "structs.h"

void flushInputs(void);

int getSingleInput(void);

void drawString(t_game*, char *, int, int, TTF_Font *, int, int);

void drawRedefine(t_game *);

void drawBackground(t_game *, int);

void drawConfig(t_game *);

void drawBtn(t_game *, int, int, int);

#endif /* __CONFIG_H__ */
