#include "fire.h"

void fireCounter(t_map_case **map, t_entity *fire)
{
	fire->life--;

	if (map[fire->x][fire->y].player != NULL &&
			map[fire->x][fire->y].player->life > 0 &&
			fire->life == FIRE_LIFETIME - 5) {
		printf("%i %i %i\n", fire->x, fire->y, map[fire->x][fire->y].player->life);
		map[fire->x][fire->y].player->life--;
	}
	if (map[fire->x][fire->y].block != NULL &&
			map[fire->x][fire->y].block->type == TYPE_BUSH &&
			fire->life == FIRE_LIFETIME - 5)
		map[fire->x][fire->y].block = NULL;
}

t_entity *addFire(t_map_case **map, int x, int y)
{
	t_entity *fire = malloc(sizeof(t_entity));

	fire->x = x;
	fire->y = y;
	fire->life = FIRE_LIFETIME;
	fire->sprite = getSprite(MAP_SPRITE_FIRE);
	fire->action = &fireCounter;
	fire->draw = &drawImage;
	map[x][y].fire = fire;

	return fire;
}
