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


int serialize_request(t_request *req, int sock)
{
	char request[BUFF_SIZE] = "";
	char buff[3];

	sprintf(buff, "%i:", req->player_nb);
	strcat(request, buff);
	sprintf(buff, "%i:", req->dir);
	strcat(request, buff);
	sprintf(buff, "%i:", req->fire);
	strcat(request, buff);
	sprintf(buff, "%i", req->ckecksum);
	strcat(request, buff);

	request[strlen(request)] =  '\0';

	printf("client: request: %s \n", request);
	if (send(sock, request, strlen(request), 0) < 0) {
		printf("Send failed\n");
		return (1);
	}
	return (0);
}

int send_deco(int sock)
{
	t_request req;
	req.fire = 0;
	req.dir = 0;
	req.player_nb = 1;
	req.ckecksum = 1;

	serialize_request(&req, sock);
	return (0);
}

int send_request(int sock)
{
	t_request req;
	req.fire = 1;
	req.dir = 0;
	req.player_nb = 1;
	req.ckecksum = 0;

	serialize_request(&req, sock);
	return (0);
}

void unserialize_response(char *buffer, t_response *tmp)
{
	char **response;
	char **buff;
	char **buff2;

//	printf("client: buffer response server size: %s\n\n", buffer);
	response = my_str_to_wordtab(buffer, ' ');
	buff = my_str_to_wordtab(response[0], ':');
	tmp->infos.game_status = atoi(buff[0]);
	tmp->infos.nb_players = atoi(buff[1]);
	tmp->infos.winner_player = atoi(buff[2]);

	buff = my_str_to_wordtab(response[1], ';');
	for (int i = 0; i < tmp->infos.nb_players; i++) {
		buff2 = my_str_to_wordtab(buff[i], ':');
		tmp->players[i]->x = atoi(buff2[0]);
		tmp->players[i]->y = atoi(buff2[1]);
		tmp->players[i]->ammo = atoi(buff2[2]);
		tmp->players[i]->reload = atoi(buff2[3]);
		tmp->players[i]->frags = atoi(buff2[4]);
		tmp->players[i]->connected = atoi(buff2[5]);
		tmp->players[i]->life = atoi(buff2[6]);
		tmp->players[i]->speed = atoi(buff2[7]);
	}

	buff = my_str_to_wordtab(response[2], ';');
	for (int i = 0; i < MAP_SIZE; ++i) {
		buff2 = my_str_to_wordtab(buff[i], ':');
		for (int j = 0; j < MAP_SIZE; ++j) {
			tmp->map[i][j].data = buff2[j];
		}
	}
}

int get_response(int sock, t_response *tmp)
{
	char buffer[BUFF_SIZE];

	if (recv(sock, buffer, BUFF_SIZE, 0) < 0) {
		puts("recv failed");
		return (1);
	}
	unserialize_response(buffer, tmp);

	return (0);
}

// TODO A REVOIR !!
int my_client(int s, t_response *tmp)
{
	int r = 0;
	printf("client: send request\n");
	r = send_request(s);
	r = get_response(s, tmp);

	return (r);
}

void client_beer_bomber(Game *game)
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go = 0;
	t_response *tmp = malloc(sizeof(t_response));
	tmp->players = malloc(MAX_PLAYER * sizeof(t_player *));
	tmp->players[0] = malloc(sizeof(t_player));
	tmp->map = load_server_map();
	tmp->infos.game_status = 0;
	tmp->infos.nb_players = 1;
	tmp->infos.winner_player = 0;

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
	my_client(sock, tmp);
	printf("test client 1\n");
	while (!go) {
		if (game->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = doRedefine(game);
		} else if (game->status == IN_GAME ||
				game->status == IN_CONFIG) {
			go = getInput(game);
			my_client(sock, tmp);
			SDL_Delay(100);
			printf("client: ammo: %i\n", tmp->players[0]->ammo);
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
	send_deco(sock);
}
