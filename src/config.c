#include "config.h"

int doConfig(Game *game)
{
	if (game->input->left == 1) {
		game->btn--;
	} else if (game->input->right == 1) {
		game->btn++;
	} else if (game->input->fire == 1) {
		return (game->btn);
	}
	(game->btn < 2) ? game->btn = 2: 0;
	(game->btn > 3) ? game->btn = 3: 0;
	drawConfig(game);

	return (0);
}

void drawConfig(Game *game)
{
	/* Blank the screen */
	SDL_RenderClear(game->renderer);

	/* Draw background */
	drawBackground(game, MAP_BACK_ONE);

	if (game->btn == 2) {
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
