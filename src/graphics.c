#include "graphics.h"


extern DECLSPEC SDL_Surface * SDLCALL IMG_Load(const char *file);

SDL_Surface *loadImage(char *name)
{
	/* Load the image using SDL Image */
	
	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;
	
	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		
		return NULL;
	}
	
	/* Make the background transparent */
	
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));
	
	/* Convert the image to the screen's native format */
	
	image = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);
	
	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);
		
		return NULL;
	}
	
	/* Return the processed image */
	
	return image;
}

void drawImage(SDL_Surface *image, int x, int y)
{
	SDL_Rect dest;
	
	/* Set the blitting rectangle to the size of the src image */
	
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	
	SDL_BlitSurface(image, NULL, game.screen, &dest);
}

void loadSprite(int index, char *name)
{
	/* Load the image into the next slot in the sprite bank */
	
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		
		exit(1);
	}
	
	sprite[index].image = loadImage(name);
	
	if (sprite[index].image == NULL)
	{
		exit(1);
	}
}

SDL_Surface *getSprite(int index)
{
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		
		exit(1);
	}
	
	return sprite[index].image;
}

void freeSprites()
{
	int i;
	
	/* Loop through the sprite bank and clear the images */
	
	for (i=0;i<MAX_SPRITES;i++)
	{
		if (sprite[i].image != NULL)
		{
			SDL_FreeSurface(sprite[i].image);
		}
	}
}

void loadAllSprites()
{
	loadSprite(BOMB_SPRITE, "gfx/bomb/bomb_stand_1.png");
	loadSprite(BOMB_SPRITE2, "gfx/bomb/bomb_stand_2.png");
	loadSprite(BOMB_SPRITE3, "gfx/bomb/bomb_stand_3.png");

    loadSprite(MAP_SPRITE_BASE, "gfx/map/base_map_1x1.png");
    loadSprite(MAP_SPRITE_BLOCK, "gfx/map/block_1x1.png");
    loadSprite(MAP_SPRITE_BUSH, "gfx/map/bush_1x1.png");
    loadSprite(MAP_SPRITE_FIRE, "gfx/map/fire_1.png");

    loadSprite(PLAYER_SPRITE1, "gfx/players/player1_1.png");
    loadSprite(PLAYER_SPRITE2, "gfx/players/player1_2.png");
    loadSprite(PLAYER_SPRITE3, "gfx/players/player1_3.png");
    loadSprite(PLAYER_SPRITE4, "gfx/players/player1_4.png");
    loadSprite(PLAYER_SPRITE5, "gfx/players/player1_5.png");
    loadSprite(PLAYER_SPRITE6, "gfx/players/player1_6.png");
    loadSprite(PLAYER_SPRITE7, "gfx/players/player1_7.png");
    loadSprite(PLAYER_SPRITE8, "gfx/players/player1_8.png");
    loadSprite(PLAYER_SPRITE9, "gfx/players/player1_9.png");
    loadSprite(PLAYER_SPRITE10, "gfx/players/player1_10.png");
}
