#include "server.h"

void allocate_fd(int fd, int type, t_player **players)
{
	t_player *player;

	if ((player = malloc(sizeof(t_player))) == NULL)
		return;
	player->fd = fd;
	player->type = type;
	player->connected = 1;
	player->speed = PLAYER_SPEED;
	player->ammo = PLAYER_MAX_AMMO;
	player->life = PLAYER_MAX_LIFE;
	player->reload = PLAYER_RELOAD_TIME;
	player->frags = 0;
	player->x = 1;
	player->y = 1;

	for (int i = 0; i < MAX_PLAYER; i++) {
		if (players[i] == NULL) {
			players[i] = player;
			return;
		}
	}
}

void client_read(int fd)
{
	int r;
	char buf[BUFF_SIZE];

	r = read(fd, buf, BUFF_SIZE);
	if (r > 0) {
		buf[r - 1] = '\0';
		printf("server: CLIENT: %s\n", buf);
	}
}

void server_read(t_env *e, int s)
{
	int cs;
	struct sockaddr_in client_sin;
	socklen_t *client_sin_len;

	cs = accept(s, (struct sockaddr *) &client_sin,
				(socklen_t * ) & client_sin_len);
	if (cs == -1)
		return;
	allocate_fd(cs, FD_CLIENT, e->players);
}

void add_server(t_env *e)
{
	int s;
	struct sockaddr_in sin;
	int pos;

	pos = 1;
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		return;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1)
		return;
	if (listen(s, MAX_PLAYER) == -1)
		return;
	allocate_fd(s, FD_SERVER, e->players);
}

int my_server(t_env *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	e->fd_max = 0;
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (e->players[i] != NULL &&
			e->players[i]->type != FD_FREE) {
			FD_SET(e->players[i]->fd, &e->fd_read);
			FD_SET(e->players[i]->fd, &e->fd_write);
			e->fd_max = e->players[i]->fd;
		}
	}
	if (select(e->fd_max + 1,
			   &e->fd_read, &e->fd_write, NULL, NULL) == -1)
		return (0);
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (e->players[i] != NULL &&
			FD_ISSET(e->players[i]->fd, &e->fd_read)) {
			if (e->players[i]->type == FD_SERVER)
				server_read(e, e->players[i]->fd);
			if (e->players[i]->type == FD_CLIENT)
				client_read(e->players[i]->fd);
		}
	}
	return (1);
}

void *server_beer_bomber()
{
	printf("server: in thread\n");


	t_env env;
	env.players = malloc(MAX_PLAYER * sizeof(t_player *));
	env.map = load_server_map();
	for (int i = 0; i < MAX_PLAYER; i++) {
		env.players[i] = NULL;
	}
	env.port = 5000;
	add_server(&env);
	while (my_server(&env)) {

	};

	pthread_exit(NULL);
}
