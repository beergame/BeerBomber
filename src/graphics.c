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

	x = (x * 2 * 16) + BOARD_WIDTH;
	y = (y * 2 * 16) + BOARD_HEIGHT;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = x;
	dest.y = y;
	dest.h = h * 2;
	dest.w = w * 2;

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

void loadPlayerTexture(Game *game, char *path, int index)
{
	SDL_Texture *clip[4][7];
	SDL_Surface *surf = IMG_Load(path);
	int width = surf->w;
	int height = surf->h;
	int clipPerRow = 4;
	int clipPerColumn = 7;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surf);
	SDL_FreeSurface(surf);
	for (int i = 0; i < clipPerRow; i++) {
		for (int j = 0; j < clipPerColumn; j++) {
			clip[i][j] = SDL_CreateTexture(
					game->renderer,
					SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET,
					width / clipPerRow, height / clipPerColumn
			);
			SDL_SetTextureBlendMode(clip[i][j], SDL_BLENDMODE_BLEND);
			SDL_Rect rect = {
					i * width / clipPerRow,
					j * height / clipPerColumn,
					width / clipPerRow,
					height / clipPerColumn
			};
			SDL_SetRenderTarget(game->renderer, clip[i][j]);
			SDL_RenderCopy(game->renderer, texture, &rect, NULL);
		}
	}
	sprite[index++].image = clip[1][0];
	sprite[index++].image = clip[0][0];
	sprite[index++].image = clip[2][0];
	sprite[index++].image = clip[3][0];
	SDL_SetRenderTarget(game->renderer, NULL);
	SDL_DestroyTexture(texture);
}

void loadAllSprites(Game *game)
{
	loadPlayerTexture(game, "gfx/players/one.png", PLAYER_ONE_UP);
	loadPlayerTexture(game, "gfx/players/two.png", PLAYER_TWO_UP);
	loadPlayerTexture(game, "gfx/players/three.png", PLAYER_THREE_UP);
	loadPlayerTexture(game, "gfx/players/four.png", PLAYER_FOUR_UP);

	loadSprite(game, BOMB_SPRITE, "gfx/bomb/bomb_stand_1.png");
	loadSprite(game, BOMB_SPRITE2, "gfx/bomb/bomb_stand_2.png");
	loadSprite(game, BOMB_SPRITE3, "gfx/bomb/bomb_stand_3.png");

	loadSprite(game, MAP_SPRITE_BASE, "gfx/map/base_map_1x1.png");
	loadSprite(game, MAP_SPRITE_BLOCK, "gfx/map/block_1x1.png");
	loadSprite(game, MAP_SPRITE_BUSH, "gfx/map/bush_1x1.png");
	loadSprite(game, MAP_SPRITE_FIRE, "gfx/map/fire_1.png");

	loadSprite(game, MAP_BACK_ONE, "gfx/background/1.png");

	loadSprite(game, BTN_NEWGAME, "gfx/btn/newgame.png");
	loadSprite(game, BTN_NEWGAME_B, "gfx/btn/newgame.png");
	loadSprite(game, BTN_JOINGAME, "gfx/btn/joingame.png");
	loadSprite(game, BTN_JOINGAME_B, "gfx/btn/joingame.png");
}

void drawBackground(Game *game, int index)
{
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	pos.h = SCREEN_HEIGHT;
	pos.w = SCREEN_WIDTH;
	SDL_RenderCopy(game->renderer, getSprite(index), NULL, &pos);
}

void drawBtn(Game *game, int x, int y, int index)
{
	SDL_Rect pos;
	int w;
	int h;

	SDL_QueryTexture(getSprite(index), NULL, NULL, &w, &h);
	pos.x = x;
	pos.y = y;
	pos.h = h;
	pos.w = w;
	SDL_RenderCopy(game->renderer, getSprite(index), NULL, &pos);
}
