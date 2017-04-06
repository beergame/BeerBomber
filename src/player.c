#include "player.h"

extern int loadSprite(char *);

extern void drawImage(SDL_Surface *, int, int);

extern Entity *addBomb(MapCase**, int, int);

extern SDL_Surface *getSprite(int);

Entity *initPlayer(MapCase **map, int x, int y)
{
    Entity *player = (Entity *) malloc(sizeof(Entity));

    player->x = x;
    player->y = y;
    player->speed = PLAYER_SPEED;
    player->thinkTime = MAX_RELOAD_TIME;
    player->sprite = getSprite(PLAYER_SPRITE1);
    player->draw = &drawImage;

    map[x][y].entity = player;

    return player;
}

void doPlayer(MapCase **map, Entity *player)
{
    int x = player->x;
    int y = player->y;

    map[x][y].entity->speed--;

    if (map[x][y].entity->speed <= 0) {
        map[x][y].entity->speed = 0;
    }

    map[x][y].entity->thinkTime--;

    if (map[x][y].entity->thinkTime <= 0) {
        map[x][y].entity->thinkTime = 0;
    }

    if (map[x][y].entity->speed <= 0) {
        if (input.up == 1) {
            if (y > 1) {
                printf("down x %i y %i \n", map[x][y].entity->x, map[x][y].entity->y--);
                map[x][y - 1].entity = map[x][y].entity;
                map[x][y - 1].entity->speed = PLAYER_SPEED;
                map[x][y].entity = NULL;
            }
        } else if (input.down == 1) {
            if (y < MAP_SIZE - 2) {
                printf("down x %i y %i \n", map[x][y].entity->x, map[x][y].entity->y++);
                map[x][y + 1].entity = map[x][y].entity;
                map[x][y + 1].entity->speed = PLAYER_SPEED;
                map[x][y].entity = NULL;
            }

        } else if (input.left == 1) {
            if (x > 1) {
                printf("down x %i y %i \n", map[x][y].entity->x--, map[x][y].entity->y);
                map[x - 1][y].entity = map[x][y].entity;
                map[x - 1][y].entity->speed = PLAYER_SPEED;
                map[x][y].entity = NULL;
            }
        } else if (input.right == 1) {
            if (x < MAP_SIZE - 2) {
                printf("down x %i y %i \n", map[x][y].entity->x++, map[x][y].entity->y);
                map[x + 1][y].entity = map[x][y].entity;
                map[x + 1][y].entity->speed = PLAYER_SPEED;
                map[x][y].entity = NULL;
            }
        }
    }

    if (input.fire == 1) {
        /* Player can only drop bomb when the thinkTime is 0 or less */

        if (map[x][y].entity->thinkTime <= 0) {
            addBomb(map, x, y + 1);

            map[x][y].entity->thinkTime = MAX_RELOAD_TIME;
        }
    }
}
