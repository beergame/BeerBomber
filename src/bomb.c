#include "bomb.h"

extern void drawStandardEntity(void);

extern SDL_Surface *getSprite(int);

static void fireStandardBomb(void);

extern void drawImage(SDL_Surface *, int, int);

Entity *addBomb(MapCase **map, int x, int y)
{
    Entity *bomb = (Entity *) malloc(sizeof(Entity));

    bomb->x = x;
    bomb->y = y;
    bomb->sprite = getSprite(BOMB_SPRITE);
    bomb->action = &fireStandardBomb;
    bomb->draw = &drawImage;
    map[x][y].entity = bomb;

    return bomb;
}

static void fireStandardBomb()
{
}
