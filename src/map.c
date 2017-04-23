#include "map.h"

void draw_map_base(t_game *game)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			drawImage(game, getSprite(MAP_SPRITE_BASE), i, j);
		}
	}
}

void draw_map_entity(t_game *game)
{
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if (game->map[i][j].data[0] == '0' &&
				 game->map[i][j].data[1] == '1') {
				drawImage(game, getSprite(MAP_SPRITE_BUSH), i, j);
			} else if (game->map[i][j].data[0] == '1') {
				drawImage(game, getSprite(MAP_SPRITE_BLOCK), i, j);
			}
			if (game->map[i][j].data[3] == '1') {
				drawImage(game, getSprite(BOMB_SPRITE), i, j);
			} else if (game->map[i][j].data[4] == '1') {
				drawImage(game, getSprite(MAP_SPRITE_FIRE), i, j);
			}
		}
	}
}

void draw_player(t_game *g)
{
	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1) {
			switch (i) {
				case 0:
					drawImage(g, getSprite(PLAYER_ONE_DOWN),
							  g->player[i]->x, g->player[i]->y);
					break;
				case 1:
					drawImage(g, getSprite(PLAYER_TWO_DOWN),
							  g->player[i]->x, g->player[i]->y);
					break;
				case 2:
					drawImage(g, getSprite(PLAYER_THREE_DOWN),
							  g->player[i]->x, g->player[i]->y);
					break;
				case 3:
					drawImage(g, getSprite(PLAYER_FOUR_DOWN),
							  g->player[i]->x, g->player[i]->y);
					break;
				default:
					drawImage(g, getSprite(PLAYER_TWO_DOWN),
							  g->player[i]->x, g->player[i]->y);
					break;
			}
		}
	}
}
