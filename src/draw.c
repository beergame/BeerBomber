#include "draw.h"

void draw(t_game *g)
{
	char text[20];

	/* Blank the screen and draw background */
	SDL_RenderClear(g->renderer);
	draw_background(g, MAP_BACK_ONE);
	/* Draw stats */
	for (int i = 0; i < MAX_PLAYER; ++i) {
		sprintf(text, "PLAYER %d", i + 1);
		draw_log_string(g, text, 50, 40 + (i * 160), g->font);
		sprintf(text, "CO: %d", g->player[i]->connected);
		draw_log_string(g, text, 50, 70 + (i * 160), g->font);
		sprintf(text, "LIFE: %d", g->player[i]->life);
		draw_log_string(g, text, 50, 100 + (i * 160), g->font);
		sprintf(text, "FRAG: %d", g->player[i]->frags);
		draw_log_string(g, text, 50, 130 + (i * 160), g->font);
		sprintf(text, "AMMO: %d", g->player[i]->ammo);
		draw_log_string(g, text, 50, 160 + (i * 160), g->font);
	}
	/* Draw map players entities */
	draw_map_base(g);
	draw_player(g);
	draw_map_entity(g);

	if (g->info->throw_bomb == 2) {
		Mix_PlayChannel(-1, g->sounds[5].effect, 0);
		g->info->throw_bomb = 0;
	}
	if (g->info->player_boost) {
		Mix_PlayChannel(-1, g->sounds[2].effect, 0);
		g->info->player_boost = 0;
	}
	if (g->info->throw_bomb == 1) {
		Mix_PlayChannel(-1, g->sounds[0].effect, 0);
		g->info->throw_bomb = 0;
	}

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

void draw_wait_for_player(t_game *g)
{
	char text[50];

	/* Blank the screen and draw background */
	SDL_RenderClear(g->renderer);
	draw_background(g, MAP_BACK_ONE);
	/* Draw co info */
	sprintf(text, "WAIT FOR PLAYER ...");
	draw_string(g, text, 50, 100, g->font, 1, 0);
	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1) {
			sprintf(text, "PLAYER %d CO !", i + 1);
			draw_string(g, text, 50, 150 + (i * 150), g->font, 1, 0);
		}
	}
	sprintf(text, "ENTER SERVER IP ADDRESS IN CLI");
	draw_string(g, text, 50, 700, g->font, 1, 0);
	/* Update the buffer */
	SDL_RenderPresent(g->renderer);
	/* Sleep briefly for better perf */
	SDL_Delay(1);
}

void draw_winner(t_game *g)
{
	char text[50];
	SDL_Event *event = NULL;

	/* Draw winner info */
	sprintf(text, "AND THE WINNER IS ...");
	draw_string(g, text, 50, 100, g->font, 1, 0);
	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1 &&
				g->player[i]->life > 0) {
			sprintf(text, "PLAYER %d !!!", i + 1);
			draw_string(g, text, 50, 150, g->font, 1, 0);
		}
	}
	sprintf(text, "PRESS ANY KEY TO CONTINUE");
	draw_string(g, text, 50, 300, g->font, 1, 0);
	/* Update the buffer */
	SDL_RenderPresent(g->renderer);
	/* Sleep briefly for better perf */
	SDL_WaitEvent(event);
}
