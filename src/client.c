#include "client.h"

int client_connect(char *ip)
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
	sin.sin_addr.s_addr = inet_addr(ip);
	if (connect(s, (const struct sockaddr *) &sin, sizeof(sin)) == -1) {
		printf("Error connect()\n");
		return (-1);
	}

	puts("client: Connected");
	return (s);
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
	req.fire = 0;

	if (g->input->up) {
		req.dir = 1;
	} else if (g->input->down) {
		req.dir = 2;
	} else if (g->input->left) {
		req.dir = 3;
	} else if (g->input->right) {
		req.dir = 4;
	} else {
		req.dir = 0;
	}
	if (g->input->fire) req.fire = 1;
	send_serialize_request(&req, s);

	return (0);
}

void unserialize_response(char *buffer, t_game *g)
{
	char **response;
	char **buff;
	char **buff2;

	if (!(response = my_str_to_wordtab(buffer, ' ')))
		return ;
	if (!(buff = my_str_to_wordtab(response[0], ':')))
		return ;
	g->info->status = atoi(buff[0]);
	g->info->max_player = atoi(buff[1]);
	g->info->winner = atoi(buff[2]);
	g->info->throw_bomb = atoi(buff[3]);
	g->info->player_boost = atoi(buff[4]);

	if (!(buff = my_str_to_wordtab(response[1], ';')))
		return ;
	for (int i = 0; i < MAX_PLAYER; i++) {
		if ((buff2 = my_str_to_wordtab(buff[i], ':'))) {
			if (g->player[i] != NULL) {
				g->player[i]->x = atoi(buff2[0]);
				g->player[i]->y = atoi(buff2[1]);
				g->player[i]->dir = atoi(buff2[2]);
				g->player[i]->ammo = atoi(buff2[3]);
				g->player[i]->reload = atoi(buff2[4]);
				g->player[i]->frags = atoi(buff2[5]);
				g->player[i]->connected = atoi(buff2[6]);
				g->player[i]->life = atoi(buff2[7]);
				g->player[i]->speed = atoi(buff2[8]);
			}
		}
	}

	if (!(buff = my_str_to_wordtab(response[2], ';')))
		return ;
	for (int i = 0; i < MAP_SIZE; ++i) {
		if (!(buff2 = my_str_to_wordtab(buff[i], ':')))
			return ;
		for (int j = 0; j < MAP_SIZE; ++j) {
			g->map[i][j].data = buff2[j];
		}
	}
}

int get_response(int sock, t_game *g)
{
	char buffer[BUFF_SIZE];

	if (recv(sock, buffer, BUFF_SIZE, 0) < 0) {
		puts("connection server failed");
		puts("trying to get response ...");
		return (1);
	}
	unserialize_response(buffer, g);

	return (0);
}

void all_players_connected(t_game *g)
{
	int a = 0;

	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1) {
			a++;
		}
	}
	if (g->info->max_player == a) {
		g->info->status = IN_CONFIG_NEW_GAME;
	}
}

int one_left(t_game *g)
{
	int a = 0;

	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (g->player[i]->connected == 1 &&
			g->player[i]->life > 0) {
			a++;
		}
	}
	if (a == 1) {
		return (1);
	}

	return (0);
}

void client_beer_bomber(t_game *game)
{
	unsigned int frame_limit = SDL_GetTicks() + 16;
	int go = 0;
	char ip[15] = "";

	init_client(game);

	/* connect to server */
	SDL_Delay(400);
	draw_wait_for_player(game);
	printf("Server beerbomber IP: ");
	fgets(ip, sizeof(ip), stdin);
	int server = client_connect(ip);
	send_request(server, game);
	SDL_Delay(100);
	get_response(server, game);

	while (!go) {
		if (game->info->status == IN_REDEFINE) {
			/* Handle the key redefining */
			go = do_redefine(game);
		} else if (game->info->status == IN_GAME ||
				   game->info->status == IN_CONFIG_NEW_GAME) {
			go = get_input(game);
			send_request(server, game);
			get_response(server, game);
			draw(game);
			if (one_left(game))
				go = 1;
		} else if (game->info->status == WAIT_FOR_PLAYER) {
			go = get_input(game);
			send_request(server, game);
			get_response(server, game);
			all_players_connected(game);
			draw_wait_for_player(game);
		}
		delay(frame_limit);
		frame_limit = SDL_GetTicks() + 16;
	}
	if (go == 1) {
		draw_winner(game);
	}

	send_deco(server);
	clean_client(game);
}
