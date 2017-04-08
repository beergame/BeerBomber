#include "entity.h"

void freeDeadEntities(MapCase **map)
{
	/* Loop through all the entities and free dead ones */

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j].bomb != NULL && map[i][j].bomb->life == 0) {
				free(map[i][j].bomb);
				map[i][j].bomb = NULL;
			}
			if (map[i][j].fire != NULL && map[i][j].fire->life == 0) {
				free(map[i][j].fire);
				map[i][j].fire = NULL;
			}
			if (map[i][j].player != NULL && map[i][j].player->life == 0) {
				free(map[i][j].player);
				map[i][j].player = NULL;
			}
		}
	}
}

void entitiesActions(MapCase **map)
{
	/* Loop through all the entities and perform their action */

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j].bomb != NULL && map[i][j].bomb->life > 0)
				map[i][j].bomb->action(map, map[i][j].bomb);
			if (map[i][j].fire != NULL && map[i][j].fire->life > 0)
				map[i][j].fire->action(map, map[i][j].fire);
		}
	}
	freeDeadEntities(map);
}

void drawEntities(Game *game, MapCase **map)
{
	/* Loop through the entities and call their draw action */

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j].bomb != NULL && map[i][j].bomb->life > 0)
				map[i][j].bomb->draw(game, map[i][j].bomb->sprite, i, j);
			if (map[i][j].player != NULL && map[i][j].player->life > 0)
				map[i][j].player->draw(game, map[i][j].player->sprite, i, j);
			if (map[i][j].block != NULL)
				map[i][j].block->draw(game, map[i][j].block->sprite, i, j);
			if (map[i][j].fire != NULL && map[i][j].fire->life > 0)
				map[i][j].fire->draw(game, map[i][j].fire->sprite, i, j);
		}
	}
}
