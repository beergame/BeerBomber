#include "fire.h"

void fireCounter(MapCase **map, Entity *fire)
{
	fire->life--;

	if (map[fire->x][fire->y].player != NULL &&
			fire->life == FIRE_LIFETIME - 5)
		map[fire->x][fire->y].player->life--;
	if (map[fire->x][fire->y].block != NULL &&
			map[fire->x][fire->y].block->type == TYPE_BUSH &&
			   fire->life == FIRE_LIFETIME - 5)
		map[fire->x][fire->y].block = NULL;
}

Entity *addFire(MapCase **map, int x, int y)
{
	Entity *fire = malloc(sizeof(Entity));

	fire->x = x;
	fire->y = y;
	fire->life = FIRE_LIFETIME;
	fire->sprite = getSprite(MAP_SPRITE_FIRE);
	fire->action = &fireCounter;
	fire->draw = &drawImage;
	map[x][y].fire = fire;

	return fire;
}
