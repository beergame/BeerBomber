#include "map.h"

void draw_map_base(t_game *game)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			drawImage(game, get_sprite(MAP_SPRITE_BASE), i, j);
		}
	}
}

void draw_one_player(t_game *g, int sprite, int i)
{
	if (g->player[i]->dir == 1) {
		drawImage(g, get_sprite(sprite),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 2) {
		drawImage(g, get_sprite(sprite + 1),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 3) {
		drawImage(g, get_sprite(sprite + 2),
				  g->player[i]->x, g->player[i]->y);
	} else if (g->player[i]->dir == 4) {
		drawImage(g, get_sprite(sprite + 3),
				  g->player[i]->x, g->player[i]->y);
	} else {
		drawImage(g, get_sprite(sprite + 1),
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
			if (game->map[i][j].data[0] == '0' &&
				 game->map[i][j].data[1] == '1') {
				drawImage(game, get_sprite(MAP_SPRITE_BUSH), i, j);
			} else if (game->map[i][j].data[0] == '1') {
				drawImage(game, get_sprite(MAP_SPRITE_BLOCK), i, j);
			}
			if (game->map[i][j].data[3] == '1') {
				drawImage(game, get_sprite(BOMB_SPRITE), i, j);
			}
			if (game->map[i][j].data[3] == '2') {
				drawImage(game, get_sprite(BOMB_SPRITE2), i, j);
			}
			if (game->map[i][j].data[3] == '3') {
				drawImage(game, get_sprite(BOMB_SPRITE3), i, j);
			}
			if (game->map[i][j].data[4] == '1') {
				drawImage(game, get_sprite(MAP_SPRITE_FIRE), i, j);
			}
			if (game->map[i][j].data[4] == '2') {
				drawImage(game, get_sprite(MAP_SPRITE_FIRE2), i, j);
			}
			if (game->map[i][j].data[4] == '3') {
				drawImage(game, get_sprite(MAP_SPRITE_FIRE3), i, j);
			}
		}
	}
}
