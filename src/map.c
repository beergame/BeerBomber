#include "map.h"

extern void drawImage(SDL_Surface *, int, int);

extern SDL_Surface *getSprite(int);

t_case_map **loadMap()
{
    t_case_map **map;

    map = (t_case_map **) malloc(MAP_SIZE * sizeof(t_case_map *));
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = (t_case_map *) malloc(sizeof(t_case_map));
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j].sprite = (SDL_Surface *) malloc(sizeof(SDL_Surface));
            map[i][j].entity.sprite = (SDL_Surface *) malloc(sizeof(SDL_Surface));
            map[i][j].entity.active = 0;

            if (i == 0 || j == 0 || i == MAP_SIZE - 1 || j == MAP_SIZE - 1) {
                map[i][j].mapType = TYPE_BLOCK;
                map[i][j].sprite = getSprite(MAP_SPRITE_BLOCK);
            } else if (!(i % 2) && !(j % 2)) {
                map[i][j].mapType = TYPE_BLOCK;
                map[i][j].sprite = getSprite(MAP_SPRITE_BLOCK);
            } else {
                map[i][j].mapType = TYPE_BASE;
                map[i][j].sprite = getSprite(MAP_SPRITE_BASE);
            }

        }
    }

    return (map);
}

void freeMap(t_case_map **map)
{
    for (int i = 0; i < MAP_SIZE; i++) {
//        free(map[i]);
    }
//    free(map);
}

void drawMap(t_case_map **map)
{
    int x = SCREEN_HEIGHT / 3;
    int y = SCREEN_WIDTH / 5;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            drawImage(map[i][j].sprite, x + (16 * i), y + (16 * j));
            if (map[i][j].entity.active)
                drawImage(map[i][j].entity.sprite, x + (16 * i), y + (16 * j));
        }
    }
}
