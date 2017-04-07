#include "map.h"

extern void *drawImage(SDL_Surface *, int, int);

extern SDL_Surface *getSprite(int);

MapCase **loadMap()
{
    MapCase **map;

    map = (MapCase **) malloc(MAP_SIZE * sizeof(MapCase *));
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = (MapCase *) malloc(sizeof(MapCase));
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j].sprite = (SDL_Surface *) malloc(sizeof(SDL_Surface));
            map[i][j].player = NULL;
            map[i][j].bomb = NULL;
            map[i][j].block = NULL;
            map[i][j].fire = NULL;

            if (i == 0 || j == 0 || i == MAP_SIZE - 1 || j == MAP_SIZE - 1) {
                map[i][j].sprite = getSprite(MAP_SPRITE_BLOCK);
            } else {
                map[i][j].sprite = getSprite(MAP_SPRITE_BASE);
            }
        }
    }

    return (map);
}

void freeMap(MapCase **map)
{
    for (int i = 0; i < MAP_SIZE; i++) {
        free(map[i]);
    }
    free(map);
}

void drawMap(MapCase **map)
{
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            drawImage(map[i][j].sprite, i, j);
        }
    }
}
