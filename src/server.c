#include "server.h"

void allocate_fd(int fd, int type, t_player **p)
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
		if (p[i] == NULL) {
			p[i] = player;
			return ;
		}
	}
}

t_request *get_player_request(int fd)
{
	int r;
	char buffer[BUFF_SIZE];

	r = read(fd, buffer, BUFF_SIZE);
	if (r > 0) {
		buffer[r] = '\0';
		printf("server: CLIENT: %s\n", buffer);
		return (unserialize_request(buffer));
	}

	return (NULL);
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
	allocate_fd(cs, FD_CLIENT, e->player);
}

void add_server(t_env *e)
{
  int s;
  struct sockaddr_in sin;

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return ;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1)
    return ;
  if (listen(s, MAX_PLAYER) == -1)
    return ;
  allocate_fd(s, FD_SERVER, e->player);
}

int my_server(t_env *e)
{
	t_request *client_req = NULL;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	e->fd_max = 0;
	for (int i = 0; i < e->info->playermax + 1; i++) {
		if (e->player[i] != NULL &&
			e->player[i]->type != FD_FREE) {
			FD_SET(e->player[i]->fd, &e->fd_read);
			FD_SET(e->player[i]->fd, &e->fd_write);
			e->fd_max = e->player[i]->fd;
		}
	}
	if (select(e->fd_max + 1,
			   &e->fd_read, &e->fd_write, NULL, NULL) == -1)
		return (0);
	for (int i = 0; i < e->info->playermax + 1; i++) {
		if (e->player[i] != NULL &&
			FD_ISSET(e->player[i]->fd, &e->fd_read)) {
			if (e->player[i]->type == FD_SERVER) {
				server_read(e, e->player[i]->fd);
			}
			if (e->player[i]->type == FD_CLIENT) {
				client_req = get_player_request(e->player[i]->fd);
			}
		}
	}

	if (client_req != NULL) {
		/* check if player can move or throw bomb */
		do_player_move(e, client_req);
		do_player_throw_bomb(e, client_req);
		do_timing_entity(e);

		if (client_req->ckecksum == 1) {
			return (0);
		}
		/* send response to player with all env data */
		return (send_response(e, e->player[client_req->nb]));
	}

	usleep(50000);
	return (1);
}

void *server_beer_bomber(void *args)
{
	printf("server: in thread\n");

	t_env env;
	env.info = malloc(sizeof(t_info));
	env.info = (t_info *) args;

	env.player = malloc(env.info->playermax * sizeof(t_player *));
	for (int i = 0; i < env.info->playermax; i++) {
		env.player[i] = NULL;
	}

	// TODO: create list for timer opti.
	env.timer = malloc(MAX_TIMER * sizeof(t_timer *));
	for (int i = 0; i < MAX_TIMER; ++i) {
		env.timer[i] = NULL;
	}

	env.map = load_server_map();
	env.port = 5000;
	add_server(&env);
	while (my_server(&env));

	pthread_exit(NULL);
}
