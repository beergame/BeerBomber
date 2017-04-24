#include "config.h"

void draw_nb_player(t_game *game, int i);

void is_new_game(t_game *game, int *c)
{
	if (game->input->left) {
		*c = *c - 1;
	} else if (game->input->right) {
		*c = *c + 1;
	} else if (game->input->fire) {
		if (*c == 2) {
			game->info->status = IN_CONFIG_NB_PLAYER;
		} else {
			game->info->status = WAIT_FOR_PLAYER;
		}
	}
	(*c < 2) ? *c = 2: 0;
	(*c > 3) ? *c = 3: 0;
	draw_is_new_game(game, *c);
}

void choose_nb_player(t_game *game, int *nb)
{
	if (game->input->left) {
		*nb = 2;
	} else if (game->input->up) {
		*nb = 3;
	} else if (game->input->right) {
		*nb = 4;
	} else if (game->input->fire) {
		game->info->status = WAIT_FOR_PLAYER;
	}
	draw_nb_player(game, *nb);
}

void draw_nb_player(t_game *game, int c)
{
	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	draw_background(game, MAP_BACK_ONE);

	switch (c) {
		case 2:
			drawBtn(game, 250, 380, BTN_2_PLAYER);
			drawBtn(game, 550, 380, BTN_3_PLAYER_B);
			drawBtn(game, 850, 380, BTN_4_PLAYER_B);
			break;
		case 3:
			drawBtn(game, 250, 380, BTN_2_PLAYER_B);
			drawBtn(game, 550, 380, BTN_3_PLAYER);
			drawBtn(game, 850, 380, BTN_4_PLAYER_B);
			break;
		case 4:
			drawBtn(game, 250, 380, BTN_2_PLAYER_B);
			drawBtn(game, 550, 380, BTN_3_PLAYER_B);
			drawBtn(game, 850, 380, BTN_4_PLAYER);
			break;
		default:
			break;
	}
	/* Update the buffer */
	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */
	SDL_Delay(1);
}


void draw_is_new_game(t_game *game, int c)
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
