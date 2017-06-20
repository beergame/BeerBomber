#ifndef __CLEAN_H__
# define __CLEAN_H__

#include "structs.h"

void free_sprites();

void free_sound(t_game *g);

void free_map(t_map **);

void close_font(TTF_Font *);

#endif /* __CLEAN_H__ */
