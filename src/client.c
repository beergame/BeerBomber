#include "client.h"

int client_connect()
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


int send_serialize_request(t_request *req, int sock)
{
	char request[BUFF_SIZE] = "";
	char buff[3];

	sprintf(buff, "%i:", req->nb);
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

int send_deco(int s)
{
	t_request req;
	req.nb = 1;
	req.dir = 0;
	req.fire = 0;
	req.ckecksum = 1;
	send_serialize_request(&req, s);

	return (0);
}

int send_request(int s, t_game *g)
{
	t_request req;
	req.nb = 1;
	req.ckecksum = 0;

	if (g->input->up) {
		req.dir = 1;
	} else if (g->input->down) {
		req.dir = 2;
	} else if (g->input->left) {
		req.dir = 3;
	} else if (g->input->right) {
		req.dir = 4;
	}
	if (g->input->fire) {
		req.fire = 1;
	}
	send_serialize_request(&req, s);

	return (0);
}

void unserialize_response(char *buffer, t_game *g)
{
	char **response;
	char **buff;
	char **buff2;

	response = my_str_to_wordtab(buffer, ' ');
	buff = my_str_to_wordtab(response[0], ':');
	g->info->status = atoi(buff[0]);
	g->info->playermax = atoi(buff[1]);
	g->info->winner = atoi(buff[2]);

	buff = my_str_to_wordtab(response[1], ';');
	for (int i = 0; i < g->info->playermax; i++) {
		buff2 = my_str_to_wordtab(buff[i], ':');
		g->player[i]->x = atoi(buff2[0]);
		g->player[i]->y = atoi(buff2[1]);
		g->player[i]->ammo = atoi(buff2[2]);
		g->player[i]->reload = atoi(buff2[3]);
		g->player[i]->frags = atoi(buff2[4]);
		g->player[i]->connected = atoi(buff2[5]);
		g->player[i]->life = atoi(buff2[6]);
		g->player[i]->speed = atoi(buff2[7]);
	}

	buff = my_str_to_wordtab(response[2], ';');
	for (int i = 0; i < MAP_SIZE; ++i) {
		buff2 = my_str_to_wordtab(buff[i], ':');
		for (int j = 0; j < MAP_SIZE; ++j) {
			g->map[i][j].data = buff2[j];
		}
	}
}

int get_response(int sock, t_game *g)
{
	char buffer[BUFF_SIZE];

	if (recv(sock, buffer, BUFF_SIZE, 0) < 0) {
		puts("recv failed");
		return (1);
	}
	unserialize_response(buffer, g);

	return (0);
}

void client_beer_bomber(t_game *game)
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go = 0;
	init_client(game);

	/* server fd */
	int server = client_connect();
	SDL_Delay(100);
	send_request(server, game);
	SDL_Delay(200);
	get_response(server, game);

	while (!go) {
		if (game->info->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = do_redefine(game);
		} else if (game->info->status == IN_GAME ||
				game->info->status == IN_CONFIG) {
			go = getInput(game);

			send_request(server, game);

			draw(game);
		}
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}
	send_deco(server);
}
