#include "entity.h"

extern void drawImage(SDL_Surface *, int, int);

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

void doEntities()
{
    int i;

    /* Loop through the entities and perform their action */

    for (i = 0; i < MAX_ENTITIES; i++) {
        self = &entity[i];
    }
}

void drawEntities(MapCase **map)
{
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j].entity != NULL)
                map[i][j].entity->draw(map[i][j].entity->sprite, i, j);
        }
    }
}

void drawStandardEntity()
{
    drawImage(self->sprite, self->x, self->y);
}
