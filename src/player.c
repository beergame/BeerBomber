#include "player.h"

extern int loadSprite(char *);

extern void drawImage(SDL_Surface *, int, int);

extern void addBomb(t_case_map**, int, int);

extern SDL_Surface *getSprite(int);

void initPlayer(t_case_map **map, int x, int y)
{
    map[x][y].entity.active = 1;
    map[x][y].entity.sprite = getSprite(PLAYER_SPRITE1);

    map[x][y].entity.x = 1;
    map[x][y].entity.y = 1;
}

void doPlayer(t_case_map **map, int x, int y)
{
    map[x][y].entity.thinkTime--;

    if (map[x][y].entity.thinkTime <= 0) {
        map[x][y].entity.thinkTime = 0;
    }

    if (input.up == 1) {
        map[x][y].entity.y -= PLAYER_SPEED;

        /* Don't allow the player to move off the screen */

        if (map[x][y].entity.y < 0) {
            map[x][y].entity.y = 0;
        }
    }

    if (input.down == 1) {
        map[x][y + 1].entity.active = 1;
        map[x][y + 1].entity.sprite = map[x][y].entity.sprite;
//        map[x][y].entity.sprite = 0;
        map[x][y].entity.active = 0;

        /* Don't allow the player to move off the screen */

        if (map[x][y].entity.y + map[x][y].entity.sprite->h >= SCREEN_HEIGHT) {
            map[x][y].entity.y = SCREEN_HEIGHT - (map[x][y].entity.sprite->h + 1);
        }
    }

    if (input.left == 1) {
        map[x][y].entity.x -= PLAYER_SPEED;

        /* Don't allow the player to move off the screen */

        if (map[x][y].entity.x < 0) {
            map[x][y].entity.x = 0;
        }
    }

    if (input.right == 1) {
        map[x][y].entity.x += PLAYER_SPEED;

        /* Don't allow the player to move off the screen */

        if (map[x][y].entity.x + map[x][y].entity.sprite->w >= SCREEN_WIDTH) {
            map[x][y].entity.x = SCREEN_WIDTH - (map[x][y].entity.sprite->w + 1);
        }
    }

    if (input.fire == 1) {
        /* You can only fire when the thinkTime is 0 or less */

        if (map[x][y].entity.thinkTime <= 0) {
//            addBomb(map, map[x][y].entity.x, map[x][y].entity.y);

            map[x][y].entity.thinkTime = MAX_RELOAD_TIME;
        }
    }
}
