#include "bush.h"

Entity *addbush(MapCase **map, int x, int y)
{
	Entity *bush = (Entity *) malloc(sizeof(Entity));

	bush->x = x;
	bush->y = y;
	bush->life = 1;
	bush->sprite = getSprite(MAP_SPRITE_BUSH);
	bush->draw = &drawImage;
	map[x][y].block = bush;

	return bush;
}

