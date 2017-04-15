#include "client.h"

void client_beer_bomber(Game *game)
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



int			my_connect(char **cmd)
{
	struct protoent	*pe;
	struct sockaddr_in	sin;
	int			s;
	int			port;

	if (cmd[1] != NULL)
		port = my_getnbr(cmd[1]);
	pe = getprotobyname("TCP");
	if (pe == NULL)
		return (-1);
	s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (s == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(cmd[0]);
	if (connect(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		my_putstr("Error connect()\n");
		return (-1);
	}
	free_tab(cmd);
	return (s);
}

int		my_client(int s)
{
	fd_set	fd_read;
	int		r;

	r = 1;
	while (r)
	{
		FD_ZERO(&fd_read);
		FD_SET(0, &fd_read);
		FD_SET(s, &fd_read);
		if (select(s + 1, &fd_read, NULL, NULL, NULL) == -1)
			r = 0;
		if (FD_ISSET(0, &fd_read))
			r = send_input(s);
		if (FD_ISSET(s, &fd_read))
			r = get_msg(s);
	}
	return (0);
}