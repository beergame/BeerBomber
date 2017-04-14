#include "main.h"

int main(void)
{
	pthread_t server;
	pthread_t client;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int onConfig = 0;
	Game *game = malloc(sizeof(Game));

	initBeerBomber(game);
	loadAllSprites(game);

	while (!onConfig) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			onConfig = doRedefine(game);
		} else if (game->status == IN_CONFIG) {
			onConfig = doConfig(game);
		}
	}

	/* On new game: start 2 thread client/server */
	if (onConfig == 2) {
		if (pthread_create(&server, NULL, serverBeerBomber, NULL)) {
			perror("pthread_create server");
			return (EXIT_FAILURE);
		}
	}
	if (onConfig == 3) {
		if (pthread_create(&client, NULL, clientBeerBomber, NULL)) {
			perror("pthread_create client");
			return (EXIT_FAILURE);
		}
	}
	if (pthread_join(client, NULL)) {
		perror("pthread_join client");
		return (EXIT_FAILURE);
	}
	if (pthread_join(server, NULL)) {
		perror("pthread_join server");
		return (EXIT_FAILURE);
	}

	cleanup(game);
	return (0);
}
