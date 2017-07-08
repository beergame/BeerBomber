#include "server.h"

void clean_server(t_env *e)
{
	free_map(e->map);
}

void set_new_player(int fd, int type, t_player *p, int m)
{
	p->fd = fd;
	p->type = type;
	p->connected = 1;
	p->speed = PLAYER_SPEED;
	p->ammo = PLAYER_MAX_AMMO;
	p->life = PLAYER_MAX_LIFE;
	p->reload = PLAYER_RELOAD_TIME;
	p->frags = 0;
	if (m == 1) {
		p->x = 1 * PRES + 50;
		p->y = 1 * PRES + 50;
	} else if (m == 2) {
		p->x = (MAP_SIZE - 2) * PRES + 40;
		p->y = (MAP_SIZE - 2) * PRES + 40;
	} else if (m == 3) {
		p->x = 1 * PRES + 50;
		p->y = (MAP_SIZE - 2) * PRES;
	} else if (m == 4) {
		p->x = (MAP_SIZE - 2) * PRES;
		p->y = 1 * PRES + 50;
	}
}

t_request *get_player_request(int fd)
{
	int r;
	char buffer[BUFF_SIZE];

	r = read(fd, buffer, BUFF_SIZE);
	if (r > 0) {
		buffer[r] = '\0';
		return (unserialize_request(buffer));
	}

	return (NULL);
}

void server_read(t_env *e, int s)
{
	int cs;
	struct sockaddr_in client_sin;
	socklen_t *client_sin_len;

	cs = accept(s, (struct sockaddr*) &client_sin,
				(socklen_t*) & client_sin_len);
	if (cs == -1)
		return ;
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (e->player[i]->connected == 0) {
			set_new_player(cs, FD_CLIENT, e->player[i], i);
			return ;
		}
	}
}

int add_server(t_env *e)
{
	int s;
	struct sockaddr_in sin;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		printf("error socket server\n");
		return (0);
	}
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
				   &(int){ 1 }, sizeof(int)) < 0) {
		printf("setsockopt(SO_REUSEADDR) failed\n");
		return (0);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(e->port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		printf("error bind server\n");
		return (0);
	}
	if (listen(s, 10) == -1) {
		printf("error listen server\n");
		return (0);
	}
	set_new_player(s, FD_SERVER, e->player[0], 0);
	return (1);
}

int my_server(t_env *e)
{
	t_request *client_req = NULL;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	e->fd_max = 0;
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (e->player[i]->connected == 1 &&
			e->player[i]->type != FD_FREE) {
			FD_SET(e->player[i]->fd, &e->fd_read);
			FD_SET(e->player[i]->fd, &e->fd_write);
			e->fd_max = e->player[i]->fd;
		}
	}
	/** set 1 min timeout */
	struct timeval tv = {60, 0};
	if (select(e->fd_max + 1,
			   &e->fd_read, &e->fd_write, NULL, &tv) == -1) {
		return (0);
	}
	for (int i = 0; i < MAX_PLAYER; i++) {
		if (e->player[i]->connected == 1 &&
			FD_ISSET(e->player[i]->fd, &e->fd_read)) {
			if (e->player[i]->type == FD_SERVER) {
				server_read(e, e->player[i]->fd);
			}
			if (e->player[i]->type == FD_CLIENT) {
				client_req = get_player_request(e->player[i]->fd);
				if (client_req != NULL) {
					/** set new dir */
					e->player[i]->dir = client_req->dir;
					/** check if player can move or throw bomb */
					do_player_move(e, client_req, i);
					do_player_throw_bomb(e, client_req, i);
					do_player_get_beer_boosted(e, e->player[i]);

					/** check if player quit */
					if (client_req->ckecksum == 1) {
						return (0);
					}

					do_timing_entity(e);
					/** send response to player with all env data */
					send_response(e, e->player[i]);
				}
			}
		}
	}

	return (1);
}

void *server_beer_bomber(void *args)
{
	printf("server: in thread\n");

	t_env env;
	env.info = malloc(sizeof(t_info));
	env.info = (t_info *) args;

	env.player = malloc(MAX_PLAYER * sizeof(t_player *));
	for (int i = 0; i < MAX_PLAYER; i++) {
		if ((env.player[i] = malloc(sizeof(t_player))) == NULL)
			break ;
		env.player[i]->x = 0;
		env.player[i]->y = 0;
		env.player[i]->dir = 2;
		env.player[i]->ammo = 0;
		env.player[i]->reload = 0;
		env.player[i]->frags = 0;
		env.player[i]->connected = 0;
		env.player[i]->life = 0;
		env.player[i]->speed = 0;
	}

	// TODO: create list for timer optimisation.
	env.timer = malloc(MAX_TIMER * sizeof(t_timer *));
	for (int i = 0; i < MAX_TIMER; ++i) {
		env.timer[i] = NULL;
	}

	env.map = load_map();
	env.port = 5000;
	if (add_server(&env))
		while (my_server(&env));
	clean_server(&env);

	pthread_exit(NULL);
}
