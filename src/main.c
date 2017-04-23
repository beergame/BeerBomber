#include "main.h"

int main(void)
{
	pthread_t server;

	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go = 0;
	int choice = 2;
	int nb_player = 2;
	t_game *game = malloc(sizeof(t_game));

	init_main(game);
	loadAllSprites(game);

	while (!go) {
		if (game->info->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = do_redefine(game);
		} else if (game->info->status == IN_CONFIG_NEW_GAME) {
			go = getInput(game);
			is_new_game(game, &choice);
		} else if (game->info->status == IN_CONFIG_NB_PLAYER) {
			game->input->fire = 0;
			go = getInput(game);
			choose_nb_player(game, &nb_player);
		} else if (game->info->status == IN_GAME || game->info->status == IN_CONFIG_IP_SERVER){
			go = 1;
		}
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	/* new game: start server thread */
	if (choice == 2) {
		game->info->playermax = nb_player;
		if (pthread_create(&server, NULL, server_beer_bomber, game->info)) {
			perror("pthread_create server");
			return (EXIT_FAILURE);
		}
	}
	client_beer_bomber(game);
	if (choice == 2) {
		if (pthread_join(server, NULL)) {
			perror("pthread_join server");
			return (EXIT_FAILURE);
		}
	}
	cleanup(game);
	return (0);
}
