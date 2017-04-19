#include "redefine.h"

int doRedefine(t_game *game)
{
	int key = -1;

	if (strlen(redefine.buffer) == 0) {
		switch (redefine.i) {
			case 0:
				strcpy(redefine.buffer, "Press key for Left");
				break;

			case 1:
				strcpy(redefine.buffer, "Press key for Right");
				break;

			case 2:
				strcpy(redefine.buffer, "Press key for Up");
				break;

			case 3:
				strcpy(redefine.buffer, "Press key for Down");
				break;

			default:
				strcpy(redefine.buffer, "Press key for Fire");
				break;
		}
	}

	flushInputs();

	key = -2;

	while (key == -2) {
		key = getSingleInput();
		if (key == 1)
			return (1);

		drawRedefine(game);
	}

	switch (redefine.i) {
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

	redefine.i++;

	redefine.buffer[0] = '\0';

	if (redefine.i == 5) {
		redefine.i = 0;
		game->status = IN_CONFIG;
	}

	return (0);
}

void drawRedefine(t_game *game)
{
	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	drawBackground(game, MAP_BACK_ONE);

	/* Draw the redefine string */
	drawString(game, redefine.buffer, 0, 0, game->font, 1, 1);

	/* Update the buffer */
	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */
	SDL_Delay(1);
}
