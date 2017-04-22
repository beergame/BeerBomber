#include "action_server.h"

void player_move(t_env *e, t_request *req, int x, int y)
{
	e->player[req->nb]->x = x;
	e->player[req->nb]->y = y;
}

void do_player_move(t_env *e, t_request *req)
{
	if (e->player[req->nb] != NULL) {
		e->player[req->nb]->speed--;
		if (e->player[req->nb]->speed < 0) {
			e->player[req->nb]->speed = 0;
		}
		int x = e->player[req->nb]->x;
		int y = e->player[req->nb]->y;
		if (req->dir && e->player[req->nb]->speed <= 0) {
			if (req->dir == 1 && y > 1 && (e->map[x][y - 1].data[0] != '1') &&
				(e->map[x][y - 1].data[3] != '1'))
				player_move(e, req, x, y - 1);
			else if (req->dir == 2 && y < MAP_SIZE - 2 &&
					 (e->map[x][y + 1].data[1] == '0') &&
					 (e->map[x][y + 1].data[3] != '1'))
				player_move(e, req, x, y + 1);
			else if (req->dir == 3 && x > 1 &&
					 (e->map[x - 1][y].data[1] == '0') &&
					 (e->map[x - 1][y].data[3] != '1'))
				player_move(e, req, x - 1, y);
			else if (req->dir == 4 && x < MAP_SIZE - 2 &&
					 (e->map[x + 1][y].data[1] == '0') &&
					 (e->map[x + 1][y].data[3] != '1'))
				player_move(e, req, x + 1, y);
			e->player[req->nb]->speed = PLAYER_SPEED;
		}
	}
}

void throw_bomb(t_env *e, t_player *p)
{
	int i = -1;
	clock_t now = clock();
	t_timer *t = malloc(sizeof(t_timer));

	t->x = p->x;
	t->y = p->y;
	t->status = 0;
	t->start = now;
	t->nb = p->fd;
	e->map[p->x][p->y].data[3] = '1';

	while (e->timer[++i] != NULL);
	e->timer[i] = t;
}

void do_player_throw_bomb(t_env *e, t_request *r)
{
	t_player *p = e->player[r->nb];
	p->reload--;
	if (p->reload < 0) {
		p->reload = 0;
	}
	if (r->fire == 1 && p->ammo > 0 &&
		e->map[p->x][p->y].data[3] != '1' &&
		e->map[p->x][p->y].data[4] != '1' &&
		p->reload <= 0) {
		throw_bomb(e, p);
		p->ammo--;
		p->reload = PLAYER_RELOAD_TIME;
	}
}

void fire_action(t_env *e)
{
	for (int i = 0; i < MAP_SIZE; ++i) {
		for (int j = 0; j < MAP_SIZE; ++j) {
			if ((e->map[i][j].data[0] == '0' &&
				e->map[i][j].data[1] == '1') &&
				e->map[i][j].data[4] == '1') {
				e->map[i][j].data[1] = '0';
			}
		}
	}
}

void throw_fire(t_env *e, t_timer *t, char c)
{
	for (int i = t->x; i < (t->x + 3); i++) {
		if (e->map[i][t->y].data[0] == '1' &&
			e->map[i][t->y].data[1] == '1') {
			break ;
		}
		e->map[i][t->y].data[4] = c;
	}
	for (int i = t->x - 1; i > (t->x - 3); i--) {
		if (e->map[i][t->y].data[0] == '1' &&
			e->map[i][t->y].data[1] == '1') {
			break ;
		}
		e->map[i][t->y].data[4] = c;
	}
	for (int i = t->y + 1; i < (t->y + 3); i++) {
		if (e->map[t->x][i].data[0] == '1' &&
			e->map[t->x][i].data[1] == '1') {
			break ;
		}
		e->map[t->x][i].data[4] = c;
	}
	for (int i = t->y - 1; i > (t->y - 3); i--) {
		if (e->map[t->x][i].data[0] == '1' &&
			e->map[t->x][i].data[1] == '1') {
			break ;
		}
		e->map[t->x][i].data[4] = c;
	}
	fire_action(e);
	t->status++;
	t->start = clock();
}

void do_timing_entity(t_env *e)
{
	int i = 0;
	clock_t now = clock();

	while (e->timer[i] != NULL) {
		if (e->timer[i]->status == 1 &&
			(now - e->timer[i]->start) > FIRE_LIFETIME) {
			throw_fire(e, e->timer[i], '0');
		}
		if (e->timer[i]->status == 0 &&
			(now - e->timer[i]->start) > BOMB_LIFETIME) {
			e->map[e->timer[i]->x][e->timer[i]->y].data[3] = '0';
			throw_fire(e, e->timer[i], '1');
		}
		i++;
	}
}
