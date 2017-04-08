#include "graphics.h"

SDL_Texture *loadImage(Game *game, char *path)
{
	/* Load the image using SDL Image */

	SDL_Texture *texture = IMG_LoadTexture(game->renderer, path);

	if (texture == NULL) {
		printf("Failed to load image %s\n", path);
		return NULL;
	}

	/* Return the processed texture */

	return texture;
}

void drawImage(Game *game, SDL_Texture *image, int x, int y)
{
	int w;
	int h;

	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	SDL_Rect dest;

	/* Set x and y in right position on the screen */

	x = (x * 16) + BOARD_HEIGHT;
	y = (y * 16) + BOARD_WIDTH;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = x;
	dest.y = y;
	dest.h = h;
	dest.w = w;


	/* Copy the entire image onto the renderer at coordinates x and y */

	SDL_RenderCopy(game->renderer, image, NULL, &dest);
}

void loadSprite(Game *game, int index, char *path)
{
	/* Load the image into the next slot in the sprite bank */

	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		exit(1);
	}

	sprite[index].image = loadImage(game, path);

	if (sprite[index].image == NULL)
		exit(1);
}

SDL_Texture *getSprite(int index)
{
	if (index >= MAX_SPRITES || index < 0) {
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		exit(1);
	}

	return sprite[index].image;
}

void freeSprites()
{
	int i;

	/* Loop through the sprite bank and clear the images */

	for (i = 0; i < MAX_SPRITES; i++) {
		if (sprite[i].image != NULL) {
			SDL_DestroyTexture(sprite[i].image);
		}
	}
}

void loadAllSprites(Game *game)
{
	loadSprite(game, BOMB_SPRITE, "gfx/bomb/bomb_stand_1.png");
	loadSprite(game, BOMB_SPRITE2, "gfx/bomb/bomb_stand_2.png");
	loadSprite(game, BOMB_SPRITE3, "gfx/bomb/bomb_stand_3.png");

	loadSprite(game, MAP_SPRITE_BASE, "gfx/map/base_map_1x1.png");
	loadSprite(game, MAP_SPRITE_BLOCK, "gfx/map/block_1x1.png");
	loadSprite(game, MAP_SPRITE_BUSH, "gfx/map/bush_1x1.png");
	loadSprite(game, MAP_SPRITE_FIRE, "gfx/map/fire_1.png");

	loadSprite(game, PLAYER_SPRITE1, "gfx/players/player1_1.png");
	loadSprite(game, PLAYER_SPRITE2, "gfx/players/player1_2.png");
	loadSprite(game, PLAYER_SPRITE3, "gfx/players/player1_3.png");
	loadSprite(game, PLAYER_SPRITE4, "gfx/players/player1_4.png");
	loadSprite(game, PLAYER_SPRITE5, "gfx/players/player1_5.png");
	loadSprite(game, PLAYER_SPRITE6, "gfx/players/player1_6.png");
	loadSprite(game, PLAYER_SPRITE7, "gfx/players/player1_7.png");
	loadSprite(game, PLAYER_SPRITE8, "gfx/players/player1_8.png");
	loadSprite(game, PLAYER_SPRITE9, "gfx/players/player1_9.png");
	loadSprite(game, PLAYER_SPRITE10, "gfx/players/player1_10.png");
}
