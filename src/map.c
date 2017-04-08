#include "map.h"

MapCase **loadMap()
{
	MapCase **tmp;

	if (!(tmp = (MapCase **) malloc(MAP_SIZE * sizeof(MapCase *)))) {
		printf("malooc error \n");

		exit(1);
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		tmp[i] = (MapCase *) malloc(sizeof(MapCase) + 400);
		if (tmp[i] == NULL) {
			printf("malooc error \n");

			exit(1);
		}
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("x");
			tmp[i][j].sprite = getSprite(MAP_SPRITE_BASE);
			tmp[i][j].player = NULL;
			tmp[i][j].bomb = NULL;
			tmp[i][j].block = NULL;
			tmp[i][j].fire = NULL;
		}
		printf("\n");
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
