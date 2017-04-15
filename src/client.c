#include "client.h"

void clientBeerBomber(Game *game)
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go = 0;

	game->map = loadMap();
	Entity *player1 = initPlayer(game->map, 1, 1);

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';
	game->input->down = 0;
	game->input->up = 0;
	game->input->right = 0;
	game->input->left = 0;
	game->input->fire = 0;

	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);
		} else if (game->status == IN_GAME) {
			go = getInput(game);
			/* Update the player's position and bomb throwing */
			if (player1 != NULL && player1->life > 0) {
				game->score = player1->life;
				playerMove(game, game->map, player1);
				playerThrowBomb(game, game->map, player1);
			} else {
				player1 = initPlayer(game->map, 1, 1);
			}
			/* Call entities's actions (bomb / fire)*/
			entitiesActions(game->map);
			/* Draw everything */
			draw(game);
		}
		/* Sleep briefly to stop sucking up all the CPU time */
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}
}
