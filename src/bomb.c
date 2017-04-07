#include "bomb.h"

void bombExplode(MapCase **map, int x, int y)
{
    for (int i = x - 2; i < x + 3; i++) {
        if (map[i][y].fire == NULL) {
            map[i][y].fire = (Entity *) malloc(sizeof(Entity));
            map[i][y].fire->sprite = getSprite(MAP_SPRITE_FIRE);
            map[i][y].fire->x = x;
            map[i][y].fire->y = y;
            map[i][y].fire->draw = &drawImage;
        }
    }

    for (int i = y - 2; i < y + 3; i++) {
        if (map[x][i].fire == NULL) {
            map[x][i].fire = (Entity *) malloc(sizeof(Entity));
            map[x][i].fire->sprite = getSprite(MAP_SPRITE_FIRE);
            map[x][i].fire->x = x;
            map[x][i].fire->y = y;
            map[x][i].fire->draw = &drawImage;
        }
    }
}

void bombCounter(MapCase **map, Entity *bomb)
{
    bomb->life--;

    if (bomb->life < 100 && bomb->life >= 50) {
        bomb->sprite = getSprite(BOMB_SPRITE2);
    } else if (bomb->life < 50 && bomb->life > 0) {
        bomb->sprite = getSprite(BOMB_SPRITE3);
    } else if (bomb->life == 0) {
        bombExplode(map, bomb->x, bomb->y);
    }
}

void freeBomb(MapCase **map)
{
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j].bomb != NULL && map[i][j].bomb->life == 0) {
                free(map[i][j].bomb);
                map[i][j].bomb = NULL;
            }
        }
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
