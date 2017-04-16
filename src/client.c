#include "client.h"

int my_connect()
{
	struct protoent *pe;
	struct sockaddr_in sin;
	int s;

	if ((pe = getprotobyname("TCP")) == NULL)
		return (-1);
	if ((s = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5000);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(s, (const struct sockaddr *) &sin, sizeof(sin)) == -1) {
		printf("Error connect()\n");
		return (-1);
	}

	puts("client: Connected");
	return (s);
}


int send_request(int sock)
{
	if (send(sock, "test client\n", strlen("test client\n"), 0) < 0) {
		printf("Send failed\n");
		return (1);
	}

	return (0);
}

int get_response(int sock)
{
	char server_response[2000];

	if (recv(sock, server_response, 2000, 0) < 0) {
		puts("recv failed");
		return (1);
	}

	return (0);
}

int my_client(int s)
{
	int r = 0;
	fd_set fd_read;
	FD_ZERO(&fd_read);
	FD_SET(0, &fd_read);
	FD_SET(s, &fd_read);
//	if (select(s + 1, &fd_read, NULL, NULL, NULL) == -1) {
//		printf("pb select\n");
//		r = 1;
//	}
	if (FD_ISSET(0, &fd_read)) {
		printf("client: send request\n");
		r = send_request(s);
	}
//	if (FD_ISSET(s, &fd_read))
//		r = get_response(s);

	return (r);
}

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

	int sock = my_connect();
	SDL_Delay(100);
	my_client(sock);
	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);
		} else if (game->status == IN_GAME ||
				game->status == IN_CONFIG) {
			go = getInput(game);
//			my_client(sock);
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
