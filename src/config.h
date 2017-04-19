#ifndef __CONFIG_H__
# define __CONFIG_H__

# include "structs.h"

void flush_inputs(void);

int get_single_input(void);

void drawString(t_game*, char *, int, int, TTF_Font *, int, int);

void draw_background(t_game *, int);

void draw_config(t_game *, int);

void drawBtn(t_game *, int, int, int);

#endif /* __CONFIG_H__ */
