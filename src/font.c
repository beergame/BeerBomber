#include "font.h"

TTF_Font *loadFont(char *name, int size)
{
	/* Use SDL_TTF to load the font at the specified size */

	TTF_Font *font = TTF_OpenFont(name, size);

	if (font == NULL) {
		printf("Failed to open Font %s: %s\n", name, TTF_GetError());

		exit(1);
	}

	return font;
}

void closeFont(TTF_Font *font)
{
	/* Close the font once we're done with it */

	if (font != NULL)
		TTF_CloseFont(font);
}

void drawString(Game *game, char *text, int x, int y, TTF_Font *font, int centerX, int centerY)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;

	/* White text on a black background */

	foregroundColor.r = 255;
	foregroundColor.g = 255;
	foregroundColor.b = 255;

	backgroundColor.r = 0;
	backgroundColor.g = 0;
	backgroundColor.b = 0;

	/* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

	surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);

	if (surface == NULL) {
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());

		return;
	}

	/* Blit the entire surface to the screen */

	dest.x = centerX ? (SCREEN_WIDTH - (surface->w * 2)) / 2 : x;
	dest.y = centerY ? (SCREEN_HEIGHT - (surface->h * 2)) / 2 : y;
	dest.w = surface->w * 2;
	dest.h = surface->h * 2;

	/* Create texture from Surface */

	texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	/* Free the generated string image */

	SDL_FreeSurface(surface);

	SDL_RenderCopy(game->renderer, texture, NULL, &dest);

	SDL_DestroyTexture(texture);
}
