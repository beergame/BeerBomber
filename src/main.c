#include "main.h"

int main(void)
{
	pthread_t server;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int config = 0;
	int go = 0;
	int choice = 2;
	t_game *game = malloc(sizeof(t_game));

	init_main(game);
	loadAllSprites(game);

	while (!go) {
		if (game->info->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = do_redefine(game);
		} else if (game->info->status == IN_CONFIG) {
			go = getInput(game);
			config = is_new_game(game, &choice);
		}
		if (config) { go = 1; }
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	/* new game: start server thread */
	if (config == 2) {
		if (pthread_create(&server, NULL, server_beer_bomber, game->info)) {
			perror("pthread_create server");
			return (EXIT_FAILURE);
		}
	}
	game->info->status = IN_GAME;
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
