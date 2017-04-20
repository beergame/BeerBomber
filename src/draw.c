#include "draw.h"

void draw(t_game *game)
{
	char text[20];

	/* Blank the screen */

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

	draw_background(game, MAP_BACK_ONE);

	/* Draw the score */

	sprintf(text, "PLAYER LIFE: %d", game->info->winner);

	drawString(game, text, 100, 10, game->font, 1, 0);

	/* Draw the map */

	draw_map_base(game);

	/* Draw the entities */

	draw_map_entity(game);

	/* Draw players */

	draw_player(game);

	/* Update the buffer */

	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */

	SDL_Delay(1);
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
		return;

	if (frameLimit > ticks + 16)
		SDL_Delay(16);
	else
		SDL_Delay(frameLimit - ticks);
}
