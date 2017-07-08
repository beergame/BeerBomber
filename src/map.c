#include "map.h"

void draw_map_base(t_game *game)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			draw_image(game, get_sprite(MAP_SPRITE_BASE), i, j, SCALE);
		}
	}
}

void draw_one_player(t_game *g, int sprite, int i)
{
	int cpt = 0;
	clock_t now = clock();
	if (((now - g->starter) * 1500 / CLOCKS_PER_SEC)
		% 1000 > PLAYER_ANIM_TIMER) {
		cpt = 1;
	}
	if (g->player[i]->dir == 1) {
		draw_player_image(g, get_sprite(sprite + cpt),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 2) {
		draw_player_image(g, get_sprite(sprite + 2 + cpt),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 3) {
		draw_player_image(g, get_sprite(sprite + 4 + cpt),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 4) {
		draw_player_image(g, get_sprite(sprite + 6 + cpt),
				  g->player[i]->x, g->player[i]->y);
	} else {
		draw_player_image(g, get_sprite(sprite + 2),
				  g->player[i]->x, g->player[i]->y);
	}
}

void draw_player(t_game *g)
{
	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1) {
			switch (i) {
				case 0:
					draw_one_player(g, PLAYER_ONE_UP, i);
					break;
				case 1:
					draw_one_player(g, PLAYER_TWO_UP, i);
					break;
				case 2:
					draw_one_player(g, PLAYER_THREE_UP, i);
					break;
				case 3:
					draw_one_player(g, PLAYER_FOUR_UP, i);
					break;
				default:
					draw_one_player(g, PLAYER_TWO_UP, i);
					break;
			}
		}
	}
}

void draw_map_entity(t_game *game)
{
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (game->map[i][j].data[5] == '1')
				draw_image(game, get_sprite(MAP_BONUS), i, j, 0.7);
			if (game->map[i][j].data[0] == '0' &&
				 game->map[i][j].data[1] == '1') {
				draw_image(game, get_sprite(MAP_SPRITE_BUSH), i, j, SCALE);
			} else if (game->map[i][j].data[0] == '1') {
				draw_image(game, get_sprite(MAP_SPRITE_BLOCK), i, j, SCALE);
			}
			if (game->map[i][j].data[3] == '1')
				draw_image(game, get_sprite(BOMB_SPRITE), i, j, SCALE);
			if (game->map[i][j].data[3] == '2')
				draw_image(game, get_sprite(BOMB_SPRITE2), i, j, SCALE);
			if (game->map[i][j].data[3] == '3')
				draw_image(game, get_sprite(BOMB_SPRITE3), i, j, SCALE);
			if (game->map[i][j].data[4] == '1')
				draw_image(game, get_sprite(MAP_SPRITE_FIRE), i, j, SCALE);
			if (game->map[i][j].data[4] == '2')
				draw_image(game, get_sprite(MAP_SPRITE_FIRE2), i, j, SCALE);
			if (game->map[i][j].data[4] == '3')
				draw_image(game, get_sprite(MAP_SPRITE_FIRE3), i, j, SCALE);
		}
	}
}
