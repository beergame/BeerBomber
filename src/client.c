#include "client.h"

void *clientBeerBomber(void *args)
{
	printf("Nous sommes dans le thread client.\n");

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go = 0;

	struct Game *game = (Game *) args;
	/* Load map */

	printf("tesy");
	game->map = loadMap();

	/* Initialise the player */

	Entity *player1 = initPlayer(game->map, 1, 1);

	/* Reset the redefine index */

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';

	/* Loop indefinitely for messages */
	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);

		} else {
			/* Get the input */

			go = getInput(game);

			/* Update the player's position and bomb throwing */

			if (player1 != NULL && player1->life > 0) {
				game->score = player1->life;
				playerMove(game->map, player1);
				playerThrowBomb(game->map, player1);
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

	pthread_exit(NULL);
}
