#include "player.h"

Entity *initPlayer(MapCase **map, int x, int y)
{
	Entity *player = (Entity *) malloc(sizeof(Entity));

	player->x = x;
	player->y = y;
	player->speed = PLAYER_SPEED;
	player->life = PLAYER_MAX_LIFE;
	player->ammo = PLAYER_MAX_AMMO;
	player->sprite = getSprite(PLAYER_SPRITE1);
	player->draw = &drawImage;

	map[x][y].player = player;

	return player;
}

void playerMove(MapCase **map, Entity *player)
{
	int x = player->x;
	int y = player->y;

	map[x][y].player->speed--;

	if (map[x][y].player->speed <= 0) {
		if (input.up == 1) {
			if (y > 1) {
				map[x][y].player->y--;
				map[x][y - 1].player = map[x][y].player;
				map[x][y - 1].player->speed = PLAYER_SPEED;
				map[x][y].player = NULL;
			}
		} else if (input.down == 1) {
			if (y < MAP_SIZE - 2) {
				map[x][y].player->y++;
				map[x][y + 1].player = map[x][y].player;
				map[x][y + 1].player->speed = PLAYER_SPEED;
				map[x][y].player = NULL;
			}

		} else if (input.left == 1) {
			if (x > 1) {
				map[x][y].player->x--;
				map[x - 1][y].player = map[x][y].player;
				map[x - 1][y].player->speed = PLAYER_SPEED;
				map[x][y].player = NULL;
			}
		} else if (input.right == 1) {
			if (x < MAP_SIZE - 2) {
				map[x][y].player->x++;
				map[x + 1][y].player = map[x][y].player;
				map[x + 1][y].player->speed = PLAYER_SPEED;
				map[x][y].player = NULL;
			}
		}
	}


}

void playerThrowBomb(MapCase **map, Entity *player)
{
	if (input.fire == 1) {
		/* Player can only drop bomb when he has ammo and isn't in fire */

		if (player->ammo > 0 && map[player->x][player->y].bomb == NULL &&
			map[player->x][player->y].fire == NULL) {
			addBomb(map, player->x, player->y);
			player->ammo--;
		}
	}
}
