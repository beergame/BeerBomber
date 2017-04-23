#ifndef __DEFS_H__
# define __DEFS_H__

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
# include <pthread.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/SDL_ttf.h"

# define SCREEN_WIDTH 1366
# define SCREEN_HEIGHT 760
# define MAP_SIZE 15
# define BOARD_WIDTH (SCREEN_WIDTH / 2) - (MAP_SIZE * 32 / 2)
# define BOARD_HEIGHT (SCREEN_HEIGHT / 2) - (MAP_SIZE * 32 / 2)
# define MAX_PLAYER 4
# define MAX_SPRITES 40
# define DEAD_ZONE 3200
# define BUFF_SIZE 3000

enum sprite
{
	PLAYER_ONE_UP,
	PLAYER_ONE_DOWN,
	PLAYER_ONE_LEFT,
	PLAYER_ONE_RIGHT,
	PLAYER_TWO_UP,
	PLAYER_TWO_DOWN,
	PLAYER_TWO_LEFT,
	PLAYER_TWO_RIGHT,
	PLAYER_THREE_UP,
	PLAYER_THREE_DOWN,
	PLAYER_THREE_LEFT,
	PLAYER_THREE_RIGHT,
	PLAYER_FOUR_UP,
	PLAYER_FOUR_DOWN,
	PLAYER_FOUR_LEFT,
	PLAYER_FOUR_RIGHT,

	BOMB_SPRITE,
	BOMB_SPRITE2,
	BOMB_SPRITE3,

	MAP_SPRITE_BASE,
	MAP_SPRITE_BLOCK,
	MAP_SPRITE_BUSH,
	MAP_SPRITE_FIRE,

	MAP_BACK_ONE,
	BTN_NEWGAME,
	BTN_NEWGAME_B,
	BTN_JOINGAME,
	BTN_JOINGAME_B,
};

enum status
{
	IN_REDEFINE,
	IN_CONFIG_NEW_GAME,
	IN_CONFIG_NB_PLAYER,
	IN_CONFIG_IP_SERVER,
	IN_GAME,
	END_GAME,
};

#endif /* __DEFS_H__ */
