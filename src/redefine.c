#include "redefine.h"

int do_redefine(t_game *game)
{
	int key = -1;

	if (strlen(game->redefine->buffer) == 0) {
		switch (game->redefine->i) {
			case 0:
				strcpy(game->redefine->buffer, "Press key for Left");
				break;

			case 1:
				strcpy(game->redefine->buffer, "Press key for Right");
				break;

			case 2:
				strcpy(game->redefine->buffer, "Press key for Up");
				break;

			case 3:
				strcpy(game->redefine->buffer, "Press key for Down");
				break;

			default:
				strcpy(game->redefine->buffer, "Press key for Fire");
				break;
		}
	}

	flush_inputs();

	key = -2;

	while (key == -2) {
		key = get_single_input();
		if (key == 1)
			return (2);

		draw_redefine(game);
	}
	Mix_PlayChannel(-1, game->sounds[3].effect, 0);

	switch (game->redefine->i) {
		case 0:
			game->control->left = key;
			break;

		case 1:
			game->control->right = key;
			break;

		case 2:
			game->control->up = key;
			break;

		case 3:
			game->control->down = key;
			break;

		default:
			game->control->fire = key;
			break;
	}

	game->redefine->i++;

	game->redefine->buffer[0] = '\0';

	if (game->redefine->i == 5) {
		game->redefine->i = 0;
		game->info->status = IN_CONFIG_NEW_GAME;
		Mix_PlayMusic( game->music, -1 );
	}

	return (0);
}

void draw_redefine(t_game *game)
{
	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	draw_background(game, MAP_BACK_ONE);

	/* Draw the redefine string */
	draw_string(game, game->redefine->buffer, 0, 0, game->font, 1, 1);

	/* Update the buffer */
	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */
	SDL_Delay(1);
}
