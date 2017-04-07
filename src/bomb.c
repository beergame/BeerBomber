#include "bomb.h"

void bombExplode(MapCase **map, int x, int y)
{
	for (int i = x - 2; i < x + 3; i++) {
		if (map[i][y].fire == NULL) {
			addFire(map, i, y);
		}
	}

	for (int i = y - 2; i < y + 3; i++) {
		if (map[x][i].fire == NULL) {
			addFire(map, x, i);
		}
	}
}

void bombCounter(MapCase **map, Entity *bomb)
{
	bomb->life--;

	if (bomb->life == 100) {
		bomb->sprite = getSprite(BOMB_SPRITE2);
	} else if (bomb->life == 50) {
		bomb->sprite = getSprite(BOMB_SPRITE3);
	} else if (bomb->life == 0) {
		printf("bomb explode\n");
		bombExplode(map, bomb->x, bomb->y);
	}
}

Entity *addBomb(MapCase **map, int x, int y)
{
	Entity *bomb = (Entity *) malloc(sizeof(Entity));

	bomb->x = x;
	bomb->y = y;
	bomb->life = BOMB_LIFETIME;
	bomb->sprite = getSprite(BOMB_SPRITE);
	bomb->action = &bombCounter;
	bomb->draw = &drawImage;
	map[x][y].bomb = bomb;

	return bomb;
}
