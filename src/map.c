#include "map.h"

t_map_case **load_map()
{
	t_map_case **tmp;

	t_entity *block = malloc(sizeof(t_entity));
	block->sprite = getSprite(MAP_SPRITE_BLOCK);
	block->draw = &drawImage;
	block->type = TYPE_BLOCK;
	block->life = 1;
	t_entity *bush = addBush();

	if (!(tmp = malloc(MAP_SIZE * sizeof(t_map_case *))))
		return (NULL);
	for (int i = 0; i < MAP_SIZE; i++) {
		if (!(tmp[i] = malloc(MAP_SIZE * sizeof(t_map_case))))
			return (NULL);
		for (int j = 0; j < MAP_SIZE; j++) {
			tmp[i][j].player = NULL;
			tmp[i][j].bomb = NULL;
			tmp[i][j].block = NULL;
			tmp[i][j].fire = NULL;

			if (i == 0 || j == 0 || i == MAP_SIZE - 1 ||
					j == MAP_SIZE - 1 || (!(i % 2) && !(j % 2))) {
				tmp[i][j].block = block;
			} else if (i != 1) {
				tmp[i][j].block = bush;
			}
		}
	}

	return tmp;
}

void free_map(t_map_case **map)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}

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