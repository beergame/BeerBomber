#include "main.h"

int main(void)
{
	pthread_t server = NULL;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int onConfig = 0;
	int go = 0;
	Game *game = malloc(sizeof(Game));

	initBeerBomber(game);
	loadAllSprites(game);

	redefine.redefineIndex = 0;
	redefine.redefineString[0] = '\0';

	game->input = malloc(sizeof(Control));
	game->customControl = malloc(sizeof(Control));
	game->input->down = 0;
	game->input->up = 0;
	game->input->right = 0;
	game->input->left = 0;
	game->input->fire = 0;

	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);
		} else if (game->status == IN_CONFIG) {
			go = getInput(game);
			onConfig = doConfig(game);
		}
		if (onConfig) {
			go = 1;
		}
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	/* On new game: start 2 thread client/server */
	if (onConfig == 2) {
		if (pthread_create(&server, NULL, serverBeerBomber, &game)) {
			perror("pthread_create server");
			return (EXIT_FAILURE);
		}
	}
	game->status = IN_GAME;
	clientBeerBomber(game);
	if (pthread_join(server, NULL)) {
		perror("pthread_join server");
		return (EXIT_FAILURE);
	}

	cleanup(game);
	return (0);
}
