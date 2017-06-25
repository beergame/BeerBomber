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

void close_font(TTF_Font *font)
{
	/* Close the font once we're done with it */

	if (font != NULL)
		TTF_CloseFont(font);
}

void draw_string(t_game *game, char *text, int x, int y, TTF_Font *font, int centerX, int centerY)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;

	/* Black text on a white background */

	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	backgroundColor.r = 255;
	backgroundColor.g = 255;
	backgroundColor.b = 255;

	/* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

	surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);

	if (surface == NULL) {
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return ;
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

void draw_log_string(t_game *g, char *text, int x, int y, TTF_Font *font)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;

	/* Black text on a white background */

	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	backgroundColor.r = 255;
	backgroundColor.g = 255;
	backgroundColor.b = 255;

	/* Use SDL_TTF to generate a string image, this returns an SDL_Surface */
	surface = TTF_RenderUTF8_Shaded(font, text, foregroundColor, backgroundColor);
	if (surface == NULL) {
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return ;
	}

	/* Blit the entire surface to the screen */
	dest.x = x;
	dest.y = y;
	dest.w = surface->w * 1.5;
	dest.h = surface->h * 1.5;

	/* Create texture from Surface */
	texture = SDL_CreateTextureFromSurface(g->renderer, surface);

	/* Free the generated string image */
	SDL_FreeSurface(surface);
	SDL_RenderCopy(g->renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
}
