#include "draw.h"

extern void drawMap(t_case_map** map);
extern void drawEntities(void);
extern void drawString(char *, int, int, TTF_Font *, int, int);

void draw()
{
	char text[20];

	/* Blank the screen */

	SDL_FillRect(game.screen, NULL, 0);

	/* Draw the score */

	sprintf(text, "SCORE: %05d", game.score);

	drawString(text, 100, 10, game.font, 1, 0);

	sprintf(text, "TIC: %05d", SDL_GetTicks());

	drawString(text, 100, 50, game.font, 1, 0);

	/* Draw the map */
	drawMap(game.map);

	/* Draw the entities */
	
	//drawEntities();
	
	/* Update the buffer */

	SDL_Flip(game.screen);
	
	/* Sleep briefly */
	
	SDL_Delay(1);
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}
