#include "draw.h"

void draw(t_game *g)
{
	char text[20];

	/* Blank the screen and draw background */
	SDL_RenderClear(g->renderer);
	draw_background(g, MAP_BACK_ONE);
	/* Draw the score */
	for (int i = 0; i < MAX_PLAYER; ++i) {
		sprintf(text, "PLAYER %d", i + 1);
		draw_log_string(g, text, 50, 20 + (i * 150), g->font);
		sprintf(text, "CO: %d", g->player[i]->connected);
		draw_log_string(g, text, 50, 40 + (i * 150), g->font);
		sprintf(text, "LIFE: %d", g->player[i]->life);
		draw_log_string(g, text, 50, 60 + (i * 150), g->font);
		sprintf(text, "FRAG: %d", g->player[i]->frags);
		draw_log_string(g, text, 50, 80 + (i * 150), g->font);
		sprintf(text, "AMMO: %d", g->player[i]->ammo);
		draw_log_string(g, text, 50, 100 + (i * 150), g->font);
	}
	/* Draw map players entities */
	draw_map_base(g);
	draw_player(g);
	draw_map_entity(g);
	/* Update the buffer */
	SDL_RenderPresent(g->renderer);
	/* Sleep briefly for better perf */
	SDL_Delay(1);
}

void delay(unsigned int frame_limit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frame_limit < ticks)
		return ;
	if (frame_limit > ticks + 16)
		SDL_Delay(16);
	else
		SDL_Delay(frame_limit - ticks);
}
