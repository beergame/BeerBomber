#include "player.h"

Entity *initPlayer(MapCase **map, int x, int y)
{
	Entity *player = malloc(sizeof(Entity));
	player->x = x;
	player->y = y;
	player->speed = PLAYER_SPEED;
	player->life = PLAYER_MAX_LIFE;
	player->ammo = PLAYER_MAX_AMMO;
	player->reload = PLAYER_RELOAD_TIME;
	player->sprite = getSprite(PLAYER_ONE_DOWN);
	player->draw = &drawImage;
	map[x][y].player = player;

	return (player);
}

void playerMoveOn(MapCase **map, Entity *player,
				  int x, int y, SDL_Texture *sprite)
{
	player->x = x;
	player->y = y;
	player->speed = PLAYER_SPEED;
	player->sprite = sprite;
	map[x][y].player = player;
	player = NULL;
}

void playerMove(MapCase **map, Entity *player) {
	int x = player->x;
	int y = player->y;
	map[x][y].player->speed--;
	if (map[x][y].player->speed <= 0)
		if (input.up == 1)
			if (y > 1 && !(map[x][y - 1].block) && !(map[x][y - 1].bomb))
				playerMoveOn(map, map[x][y].player,
							 x, y - 1, getSprite(PLAYER_ONE_UP));
		else if (input.down == 1)
				if (y < MAP_SIZE - 2 && !(map[x][y + 1].block) &&
					!(map[x][y + 1].bomb))
					playerMoveOn(map, map[x][y].player,
								 x, y + 1, getSprite(PLAYER_ONE_DOWN));
		else if (input.left == 1)
				if (x > 1 && !(map[x - 1][y].block) && !(map[x - 1][y].bomb))
					playerMoveOn(map, map[x][y].player,
								 x, y - 1, getSprite(PLAYER_ONE_LEFT));
		else if (input.right == 1)
				if (x < MAP_SIZE - 2 && !(map[x + 1][y].block) &&
					!(map[x + 1][y].bomb))
					playerMoveOn(map, map[x][y].player,
								 x, y - 1, getSprite(PLAYER_ONE_RIGHT));
}

void playerThrowBomb(MapCase **map, Entity *player)
{
	if (input.fire == 1) {
		player->reload--;
		if (player->ammo > 0 &&
				map[player->x][player->y].bomb == NULL &&
				map[player->x][player->y].fire == NULL &&
				player->reload <= 0) {
			addBomb(map, player->x, player->y);
			player->ammo--;
			player->reload = PLAYER_RELOAD_TIME;
		}
	}
}
