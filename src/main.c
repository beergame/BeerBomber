#include "main.h"

int main(void)
{
//	pthread_t server;
	pthread_t client;

	printf("Avant la création du thread.\n");

	if (pthread_create(&client, NULL, clientBeerBomber, NULL)) {
		perror("pthread_create client");
		return (EXIT_FAILURE);
	}

	if (pthread_join(client, NULL)) {
		perror("pthread_join client");
		return (EXIT_FAILURE);
	}

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;

	Game *game = malloc(sizeof(Game));
	/* Start SDL */

	initBeerBomber(game);

	go = 0;

	/* Load all the sprites */

	loadAllSprites(game);

	/* Load the font */

	game->font = loadFont("font/blackWolf.ttf", 16);

	/* Load map */

	game->map = loadMap();

	/* Initialise the player */

	Entity *player1 = initPlayer(game->map, 1, 1);

	/* Reset the redefine index */

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';

	/* Loop indefinitely for messages */

	while (go == 0) {
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

	/* Clean and exit the program */

	cleanup(game);

	return (0);
}
