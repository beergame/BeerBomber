#include "main.h"

int main(void)
{
//	pthread_t server;
	pthread_t client = NULL;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int onConfig = 0;
	int go = 0;
	Game *game = malloc(sizeof(Game));

	initBeerBomber(game);
	loadAllSprites(game);

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';

	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);
		} else if (game->status == IN_CONFIG) {
			go = getInput(game);
			onConfig = doConfig(game);
		}
		if (onConfig)
			go = 1;
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	/* On new game: start 2 thread client/server */
//	if (onConfig == 2) {
//		if (pthread_create(&server, NULL, serverBeerBomber, &game)) {
//			perror("pthread_create server");
//			return (EXIT_FAILURE);
//		}
//	}
	if (onConfig == 3) {
		game->status = IN_GAME;
		if (pthread_create(&client, NULL, clientBeerBomber, (void *)game)) {
			perror("pthread_create client");
			return (EXIT_FAILURE);
		}
	}
	if (pthread_join(client, NULL)) {
		perror("pthread_join client");
		return (EXIT_FAILURE);
	}
//	if (pthread_join(server, NULL)) {
//		perror("pthread_join server");
//		return (EXIT_FAILURE);
//	}

	cleanup(game);
	return (0);
}
