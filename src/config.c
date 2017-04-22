#include "config.h"

void is_new_game(t_game *game, int *c)
{
	if (game->input->left) {
		*c = *c - 1;
	} else if (game->input->right) {
		*c = *c + 1;
	} else if (game->input->fire) {
		game->info->status = IN_GAME;
	}
	(*c < 2) ? *c = 2: 0;
	(*c > 3) ? *c = 3: 0;
	draw_config(game, *c);
}

void draw_config(t_game *game, int c)
{
	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	draw_background(game, MAP_BACK_ONE);

	if (c == 2) {
		drawBtn(game, 300, 380, BTN_NEWGAME);
		drawBtn(game, 800, 380, BTN_JOINGAME_B);
	} else {
		drawBtn(game, 300, 380, BTN_NEWGAME_B);
		drawBtn(game, 800, 380, BTN_JOINGAME);
	}

	/* Update the buffer */
	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */
	SDL_Delay(1);
}
