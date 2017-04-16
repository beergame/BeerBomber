#include "main.h"

int main(void)
{
	pthread_t server = NULL;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int config = 0;
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
			config = is_new_game(game);
		}
		if (config) {
			go = 1;
		}
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	/* new game: start server thread */
	if (config == 2) {
		if (pthread_create(&server, NULL, server_beer_bomber, NULL)) {
			perror("pthread_create server");
			return (EXIT_FAILURE);
		}
	}
	game->status = IN_GAME;
	SDL_Delay(1000);
	client_beer_bomber(game);
	if (config == 2) {
		if (pthread_join(server, NULL)) {
			perror("pthread_join server");
			return (EXIT_FAILURE);
		}
	}
	cleanup(game);
	return (0);
}
