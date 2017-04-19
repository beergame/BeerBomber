#include "draw.h"

void draw(t_game *game)
{
	char text[20];

	/* Blank the screen */

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

	drawBackground(game, MAP_BACK_ONE);

	/* Draw the score */

	sprintf(text, "PLAYER LIFE: %d", game->score);

	drawString(game, text, 100, 10, game->font, 1, 0);

	/* Draw the map */

	draw_map(game);

	/* Draw the entities */

	drawEntities(game, game->map);

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
