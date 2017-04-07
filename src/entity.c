#include "entity.h"

extern void drawImage(SDL_Surface *, int, int);

extern void freeBomb(MapCase **);

void clearEntities()
{
    int i;

    /* Clear the list */

    for (i = 0; i < MAX_ENTITIES; i++) {
        memset(&entity[i], 0, sizeof(Entity));
    }
}

int getFreeEntity()
{
    int i;

    /* Loop through all the entities and find a free slot */

    for (i = 0; i < MAX_ENTITIES; i++) {}

    /* Return -1 if you couldn't any free slots */

    return -1;
}

void doEntities(MapCase **map)
{
    /* Loop through the entities and perform their action */

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j].bomb != NULL && map[i][j].bomb->life > 0)
                map[i][j].bomb->action(map, map[i][j].bomb);
            /*if (map[i][j].player != NULL)
                map[i][j].player->draw(map[i][j].player->sprite, i, j);
            if (map[i][j].block != NULL)
                map[i][j].block->draw(map[i][j].block->sprite, i, j);
            if (map[i][j].fire != NULL)
                map[i][j].fire->draw(map[i][j].fire->sprite, i, j);*/
        }
    }
   freeBomb(map);
}

void drawEntities(MapCase **map)
{
    /* Loop through the entities and draw it */

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j].bomb != NULL && map[i][j].bomb->life > 0)
                map[i][j].bomb->draw(map[i][j].bomb->sprite, i, j);
            if (map[i][j].player != NULL)
                map[i][j].player->draw(map[i][j].player->sprite, i, j);
            if (map[i][j].block != NULL)
                map[i][j].block->draw(map[i][j].block->sprite, i, j);
            if (map[i][j].fire != NULL)
                map[i][j].fire->draw(map[i][j].fire->sprite, i, j);
        }
    }
}

void drawStandardEntity()
{
    drawImage(self->sprite, self->x, self->y);
}
