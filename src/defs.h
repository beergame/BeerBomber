#ifndef __DEFS_H__
# define __DEFS_H__

#ifdef      __WIN32__
#define         _BSD_SOURCE
#ifndef         _WIN32_WINNT
#define         _WIN32_WINNT 0x0501
#endif

#include        <winsock2.h>
#include        <winsock.h>
#include        <windows.h>
#include        <ws2tcpip.h>
#include        <stdio.h>
#else

# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netdb.h>
#endif

# include <stdio.h>
# include <string.h>
# include <time.h>
# include <stdlib.h>

# include <pthread.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/SDL_ttf.h"

# define SCREEN_WIDTH 1366
# define SCREEN_HEIGHT 760
# define MAP_SIZE 15
# define BOARD_WIDTH (SCREEN_WIDTH / 2) - (MAP_SIZE * 48 / 2)
# define BOARD_HEIGHT (SCREEN_HEIGHT / 2) - (MAP_SIZE * 48 / 2)
# define MAX_PLAYER 4
# define MAX_SPRITES 60
# define DEAD_ZONE 4200
# define BUFF_SIZE 2500
# define PRES 100
# define PLAYER_ANIM_TIMER 500
# define SCALE 3

enum sprite
{
	PLAYER_ONE_UP,
	PLAYER_ONE_UP2,
	PLAYER_ONE_DOWN,
	PLAYER_ONE_DOWN2,
	PLAYER_ONE_LEFT,
	PLAYER_ONE_LEFT2,
	PLAYER_ONE_RIGHT,
	PLAYER_ONE_RIGHT2,
	PLAYER_TWO_UP,
	PLAYER_TWO_UP2,
	PLAYER_TWO_DOWN,
	PLAYER_TWO_DOWN2,
	PLAYER_TWO_LEFT,
	PLAYER_TWO_LEFT2,
	PLAYER_TWO_RIGHT,
	PLAYER_TWO_RIGHT2,
	PLAYER_THREE_UP,
	PLAYER_THREE_UP2,
	PLAYER_THREE_DOWN,
	PLAYER_THREE_DOWN2,
	PLAYER_THREE_LEFT,
	PLAYER_THREE_LEFT2,
	PLAYER_THREE_RIGHT,
	PLAYER_THREE_RIGHT2,
	PLAYER_FOUR_UP,
	PLAYER_FOUR_UP2,
	PLAYER_FOUR_DOWN,
	PLAYER_FOUR_DOWN2,
	PLAYER_FOUR_LEFT,
	PLAYER_FOUR_LEFT2,
	PLAYER_FOUR_RIGHT,
	PLAYER_FOUR_RIGHT2,
	BOMB_SPRITE,
	BOMB_SPRITE2,
	BOMB_SPRITE3,
	MAP_SPRITE_BASE,
	MAP_SPRITE_BLOCK,
	MAP_SPRITE_BUSH,
	MAP_SPRITE_FIRE,
	MAP_SPRITE_FIRE2,
	MAP_SPRITE_FIRE3,
	MAP_BACK_ONE,
	MAP_BONUS,
	BTN_NEWGAME,
	BTN_NEWGAME_B,
	BTN_JOINGAME,
	BTN_JOINGAME_B,
	BTN_2_PLAYER,
	BTN_2_PLAYER_B,
	BTN_3_PLAYER,
	BTN_3_PLAYER_B,
	BTN_4_PLAYER,
	BTN_4_PLAYER_B,
};

enum status
{
	IN_REDEFINE,
	IN_CONFIG_NEW_GAME,
	IN_CONFIG_NB_PLAYER,
	IN_CONFIG_IP_SERVER,
	WAIT_FOR_PLAYER,
	IN_GAME,
	END_GAME,
};

#endif /* __DEFS_H__ */
