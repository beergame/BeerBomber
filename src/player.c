#include "player.h"

extern int loadSprite(char *);

extern void drawImage(SDL_Surface *, int, int);
/*
extern void addBomb(t_case_map**, int, int);*/

extern SDL_Surface *getSprite(int);

void initPlayer(t_case_map **map, int x, int y)
{
    Entity *player = (Entity *) malloc(sizeof(Entity));

    player->active = 1;
    player->sprite = getSprite(PLAYER_SPRITE1);
    player->draw = drawImage(player->sprite, x, y);

    map[x][y].entity = player;
}

void doPlayer(t_case_map **map, int x, int y)
{
//    map[x][y].entity.thinkTime--;
//
//    if (map[x][y].entity.thinkTime <= 0) {
//        map[x][y].entity.thinkTime = 0;
//    }

    if (input.up == 1) {

    }

    if (input.down == 1) {
/*        map[x][y + 1].entity.active = 1;
        map[x][y + 1].entity.sprite = map[x][y].entity.sprite;
        map[x][y].entity.sprite = NULL;
        map[x][y].entity.active = 0;*/
    }

    if (input.left == 1) {

    }

    if (input.right == 1) {

    }

//    if (input.fire == 1) {
//        /* You can only fire when the thinkTime is 0 or less */
//
//        if (map[x][y].entity.thinkTime <= 0) {
//            addBomb(map, map[x][y].entity.x, map[x][y].entity.y);
//
//            map[x][y].entity.thinkTime = MAX_RELOAD_TIME;
//        }
//    }
}
