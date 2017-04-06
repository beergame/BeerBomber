#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BOARD_WIDTH (SCREEN_WIDTH / 5)
#define BOARD_HEIGHT (SCREEN_HEIGHT / 3)

#define MAP_SIZE 15
#define MAX_PLAYER 4

#define MAX_ENTITIES 20
#define MAX_RELOAD_TIME 10

#define MAX_SPRITES 40
#define PLAYER_SPEED 20

#define IN_REDEFINE 0
#define IN_GAME 1

#define DEAD_ZONE 3200

enum sprite
{
	PLAYER_SPRITE1,
	PLAYER_SPRITE2,
	PLAYER_SPRITE3,
	PLAYER_SPRITE4,
	PLAYER_SPRITE5,
	PLAYER_SPRITE6,
	PLAYER_SPRITE7,
	PLAYER_SPRITE8,
	PLAYER_SPRITE9,
	PLAYER_SPRITE10,

	BOMB_SPRITE,
	BOMB_SPRITE2,
	BOMB_SPRITE3,

	MAP_SPRITE_BASE,
	MAP_SPRITE_BLOCK,
	MAP_SPRITE_BUSH,
	MAP_SPRITE_FIRE,
};

enum map
{
	TYPE_BLOCK,
	TYPE_BASE,
	TYPE_BUSH
};
