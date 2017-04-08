#include "map.h"

void loadMap(MapCase **map)
{
	MapCase **tmp;

	if (!(tmp = (MapCase **) malloc(MAP_SIZE * sizeof(MapCase *)))) {
		printf("malooc error \n");

		exit(1);
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		tmp[i] = (MapCase *) malloc(sizeof(MapCase));
		if (tmp[i] == NULL) {
			printf("malooc error \n");

			exit(1);
		}
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("x");
			tmp[i][j].type = 0;
			tmp[i][j].player = NULL;
			tmp[i][j].bomb = NULL;
			tmp[i][j].block = NULL;
			tmp[i][j].fire = NULL;
		}
		printf("\n");
	}

	map = tmp;
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

void drawMap(MapCase **map)
{
	printf("toto %i\n", map[1][1].type);
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("test\n");
			if (1) {
				drawImage(getSprite(map[i][j].type), i, j);
			}
		}
	}
}
