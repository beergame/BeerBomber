#include "config.h"

void draw_nb_player(t_game *game, int i);

void is_new_game(t_game *game, int *c)
{
	if (game->input->left && (*c == 3)) {
		Mix_PlayChannel(-1, game->sounds[6].effect, 0);
		(*c)--;
	} else if (game->input->right && (*c == 2)) {
		Mix_PlayChannel(-1, game->sounds[6].effect, 0);
		(*c)++;
	} else if (game->input->fire) {
		Mix_PlayChannel(-1, game->sounds[3].effect, 0);
		if (*c == 2) {
			game->info->status = IN_CONFIG_NB_PLAYER;
		} else {
			game->info->status = WAIT_FOR_PLAYER;
		}
	}
	draw_is_new_game(game, *c);
}

void choose_nb_player(t_game *game, int *nb)
{
	if (game->input->left && (*nb != 2)) {
		Mix_PlayChannel(-1, game->sounds[6].effect, 0);
		*nb = 2;
	} else if (game->input->up && (*nb != 3)) {
		Mix_PlayChannel(-1, game->sounds[6].effect, 0);
		*nb = 3;
	} else if (game->input->right && (*nb != 4)) {
		Mix_PlayChannel(-1, game->sounds[6].effect, 0);
		*nb = 4;
	} else if (game->input->fire) {
		Mix_PlayChannel(-1, game->sounds[3].effect, 0);
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
			draw_btn(game, 250, 380, BTN_2_PLAYER);
			draw_btn(game, 550, 380, BTN_3_PLAYER_B);
			draw_btn(game, 850, 380, BTN_4_PLAYER_B);
			break;
		case 3:
			draw_btn(game, 250, 380, BTN_2_PLAYER_B);
			draw_btn(game, 550, 380, BTN_3_PLAYER);
			draw_btn(game, 850, 380, BTN_4_PLAYER_B);
			break;
		case 4:
			draw_btn(game, 250, 380, BTN_2_PLAYER_B);
			draw_btn(game, 550, 380, BTN_3_PLAYER_B);
			draw_btn(game, 850, 380, BTN_4_PLAYER);
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
	char text[50];

	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	draw_background(game, MAP_BACK_ONE);

	if (c == 2) {
		draw_btn(game, 300, 380, BTN_NEWGAME);
		draw_btn(game, 800, 380, BTN_JOINGAME_B);
	} else {
		draw_btn(game, 300, 380, BTN_NEWGAME_B);
		draw_btn(game, 800, 380, BTN_JOINGAME);
	}

	sprintf(text, "BEER BOMBER THE GAME.");
	draw_string(game, text, 50, 150, game->font, 1, 0);

	/* Update the buffer */
	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */
	SDL_Delay(1);
}
