#include "bush.h"

Entity *addBush()
{
	Entity *bush = malloc(sizeof(Entity));
	bush->sprite = getSprite(MAP_SPRITE_BUSH);
	bush->draw = &drawImage;
	bush->type = TYPE_BUSH;
	bush->life = 1;

	return (bush);
}

