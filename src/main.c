#include "main.h"

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;

	/* Start up SDL */

	init("BeerBomber");

	/* Call the cleanup function when the program exits */

	atexit(cleanup);

	go = 1;

	/* Load all the sprites */

	loadAllSprites();

	/* Load the font */

	game.font = loadFont("font/blackWolf.ttf", 16);

	/* Load map */

	game.map = loadMap();

	/* Initialise the player */

	Entity *player1 = initPlayer(game.map, 1, 1);

	/* Reset the redefine index */

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';

	/* Loop indefinitely for messages */

	while (go == 1) {
		if (game.status == IN_REDEFINE) {
			/* Handle the key redefining */

			doRedefine();
		} else {
			/* Get the input */

			getInput();

			/* Update the player's position and bomb throwing */

			if (player1 != NULL && player1->life > 0) {
				playerMove(game.map, player1);
				playerThrowBomb(game.map, player1);
			} else {
				player1 = initPlayer(game.map, 1, 1);
			}
			game.score = player1->life;

			/* Call entities's actions */

			entitiesActions(game.map);

			/* Do the collisions */

			//doCollisions();

			/* Draw everything */

			draw();
		}

		/* Sleep briefly to stop sucking up all the CPU time */

		delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;
	}

	/* Exit the program */

	return (0);
}
