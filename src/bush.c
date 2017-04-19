#include "bush.h"

t_entity *addBush()
{
	t_entity *bush = malloc(sizeof(t_entity));
	bush->sprite = getSprite(MAP_SPRITE_BUSH);
	bush->draw = &drawImage;
	bush->type = TYPE_BUSH;
	bush->life = 1;

	return (bush);
}

