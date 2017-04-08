#include "map.h"

MapCase **loadMap()
{
	MapCase **tmp;

	Entity *block = malloc(sizeof(Entity));
	block->sprite = getSprite(MAP_SPRITE_BLOCK);
	block->draw = &drawImage;
	block->type = TYPE_BLOCK;
	block->life = 1;
	Entity *bush = addBush();

	if (!(tmp = malloc(MAP_SIZE * sizeof(MapCase *)))) {
		printf("malooc error \n");

		exit(1);
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		if (!(tmp[i] = malloc(sizeof(MapCase)))) {
			printf("malooc error \n");

			exit(1);
		}
		for (int j = 0; j < MAP_SIZE; j++) {
			tmp[i][j].sprite = malloc(100); /* OMFFG DAMN BUGS SDL 2.0 */
			tmp[i][j].sprite = getSprite(MAP_SPRITE_BASE);
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

void freeMap(MapCase **map)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}

void drawMap(Game *game, MapCase **map)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			drawImage(game, map[i][j].sprite, i, j);
		}
	}
}
