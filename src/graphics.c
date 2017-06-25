#include "graphics.h"

SDL_Texture *load_image(t_game *game, char *path)
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

void draw_image(t_game *game, SDL_Texture *image, int x, int y, double scale)
{
	int w;
	int h;

	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	SDL_Rect dest;

	/**
	 * Set x and y in right position on the screen
	 * x3 for board scale
	 * x16 for sprite size 16px
	 **/
	x = (x * 3 * 16) + BOARD_WIDTH;
	y = (y * 3 * 16) + BOARD_HEIGHT;

	/* Set the blitting rectangle to the size of the src image */
	dest.x = x;
	dest.y = y;
	dest.h = h * scale;
	dest.w = w * scale;
	/* Copy the entire image onto the renderer at coordinates x and y */
	SDL_RenderCopy(game->renderer, image, NULL, &dest);
}

void draw_player_image(t_game *game, SDL_Texture *image, int x, int y)
{
	int w;
	int h;
	double xt = x;
	double yt = y;

	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	SDL_Rect dest;

	/* Set the blitting rectangle to the size of the src image */
	dest.x = (xt / PRES * 3 * 16) + BOARD_WIDTH - 20;
	dest.y = (yt / PRES * 3 * 16) + BOARD_HEIGHT - 20;
	dest.h = h * 2;
	dest.w = w * 2;

	/* Copy the entire image onto the renderer at coordinates x and y */
	SDL_RenderCopy(game->renderer, image, NULL, &dest);
}

void load_sprite(t_game *game, int index, char *path)
{
	sprite[index].image = load_image(game, path);
}

SDL_Texture *get_sprite(int index)
{
	if (index >= MAX_SPRITES || index < 0) {
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		exit(1);
	}

	return sprite[index].image;
}

void free_sprites()
{
	int i;

	/* Loop through the sprite bank and clear the images */
	for (i = 0; i < MAX_SPRITES; i++) {
		if (sprite[i].image != NULL) {
			SDL_DestroyTexture(sprite[i].image);
		}
	}
}

void load_player_texture(t_game *game, char *path, int index)
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
			SDL_SetTextureAlphaMod(clip[i][j], 255);
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
	sprite[index++].image = clip[1][1];
	sprite[index++].image = clip[1][3];
	sprite[index++].image = clip[0][1];
	sprite[index++].image = clip[0][3];
	sprite[index++].image = clip[2][1];
	sprite[index++].image = clip[2][3];
	sprite[index++].image = clip[3][1];
	sprite[index++].image = clip[3][3];
	SDL_SetRenderTarget(game->renderer, NULL);
	SDL_DestroyTexture(texture);
}

void load_all_sprites(t_game *game)
{
	load_player_texture(game, "gfx/players/one.png", PLAYER_ONE_UP);
	load_player_texture(game, "gfx/players/one.png", PLAYER_ONE_UP);
	load_player_texture(game, "gfx/players/two.png", PLAYER_TWO_UP);
	load_player_texture(game, "gfx/players/three.png", PLAYER_THREE_UP);
	load_player_texture(game, "gfx/players/four.png", PLAYER_FOUR_UP);
	load_sprite(game, BOMB_SPRITE, "gfx/bomb/tnt.png");
	load_sprite(game, BOMB_SPRITE2, "gfx/bomb/bomb_stand_2.png");
	load_sprite(game, BOMB_SPRITE3, "gfx/bomb/bomb_stand_3.png");
	load_sprite(game, MAP_SPRITE_BASE, "gfx/map/base_map_1x1.png");
	load_sprite(game, MAP_SPRITE_BLOCK, "gfx/map/block_1x1.png");
	load_sprite(game, MAP_SPRITE_BUSH, "gfx/map/bush_1x1.png");
	load_sprite(game, MAP_SPRITE_FIRE, "gfx/map/fire_1.png");
	load_sprite(game, MAP_SPRITE_FIRE2, "gfx/map/fire_2.png");
	load_sprite(game, MAP_SPRITE_FIRE3, "gfx/map/fire_3.png");
	load_sprite(game, MAP_BACK_ONE, "gfx/background/1.png");
	load_sprite(game, BTN_NEWGAME, "gfx/btn/newgame.png");
	load_sprite(game, BTN_NEWGAME_B, "gfx/btn/newgame_b.png");
	load_sprite(game, BTN_JOINGAME, "gfx/btn/joingame.png");
	load_sprite(game, BTN_JOINGAME_B, "gfx/btn/joingame_b.png");
	load_sprite(game, BTN_2_PLAYER, "gfx/btn/2_player.png");
	load_sprite(game, BTN_3_PLAYER, "gfx/btn/3_player.png");
	load_sprite(game, BTN_4_PLAYER, "gfx/btn/4_player.png");
	load_sprite(game, BTN_2_PLAYER_B, "gfx/btn/2_player_b.png");
	load_sprite(game, BTN_3_PLAYER_B, "gfx/btn/3_player_b.png");
	load_sprite(game, BTN_4_PLAYER_B, "gfx/btn/4_player_b.png");
	load_sprite(game, MAP_BONUS, "gfx/map/beer.png");
}

void draw_background(t_game *game, int index)
{
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	pos.h = SCREEN_HEIGHT;
	pos.w = SCREEN_WIDTH;
	SDL_RenderCopy(game->renderer, get_sprite(index), NULL, &pos);
}

void draw_btn(t_game *game, int x, int y, int index)
{
	SDL_Rect pos;
	int w;
	int h;
	SDL_QueryTexture(get_sprite(index), NULL, NULL, &w, &h);
	pos.x = x;
	pos.y = y;
	pos.h = h;
	pos.w = w;
	SDL_RenderCopy(game->renderer, get_sprite(index), NULL, &pos);
}
