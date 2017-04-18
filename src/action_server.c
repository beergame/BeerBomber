#include "action_server.h"

void player_move(t_env *e, t_request *req, int x, int y)
{
	e->players[req->player_nb]->x = x;
	e->players[req->player_nb]->y = y;
}

void do_player_move(t_env *e, t_request *req)
{
	if (e->players[req->player_nb] != NULL) {
		int x = e->players[req->player_nb]->x;
		int y = e->players[req->player_nb]->y;
		if (req->dir) {
			if (req->dir == 1 && y > 1 && (e->map[x][y - 1].data[1] != '1') &&
				(e->map[x][y - 1].data[3] != '1'))
				player_move(e, req, x, y - 1);
			else if (req->dir == 2 && y < MAP_SIZE - 2 &&
					 (e->map[x][y + 1].data[1] != '1') &&
					 (e->map[x][y + 1].data[3] != '1'))
				player_move(e, req, x, y + 1);
			else if (req->dir == 3 && x > 1 &&
					 (e->map[x - 1][y].data[1] != '1') &&
					 (e->map[x - 1][y].data[3] != '1'))
				player_move(e, req, x - 1, y);
			else if (req->dir == 4 && x < MAP_SIZE - 2 &&
					 (e->map[x + 1][y].data[1] != '1') &&
					 (e->map[x + 1][y].data[3] != '1'))
				player_move(e, req, x + 1, y);
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
	t->player_nb = p->fd;
	e->map[p->x][p->y].data[3] = '1';

	while (e->timers[++i] != NULL);
	e->timers[i] = t;
}

void do_player_throw_bomb(t_env *e, t_request *r)
{
	t_player *p = e->players[r->player_nb];
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

void bomb_explose(t_env *e, t_timer *t)
{
//	t_player *p = e->players[t->player_nb];
	for (int i = t->x; i < t->x + 3; i++) {
		if (e->map[i][t->y].data[1] == '1' &&
			e->map[i][t->y].data[0] == '1')
			break;
		e->map[i][t->y].data[4] = '1';
	}

	for (int i = t->x - 1; i > t->x - 3; i--) {
		if (e->map[i][t->y].data[1] == '1' &&
			e->map[i][t->y].data[0] == '1')
			break;
		e->map[i][t->y].data[4] = '1';
	}

	for (int i = t->y + 1; i < t->y + 3; i++) {
		if (e->map[t->x][i].data[1] == '1' &&
			e->map[t->x][i].data[0] == '1')
			break;
		e->map[t->x][i].data[4] = '1';
	}

	for (int i = t->y - 1; i > t->y - 3; i--) {
		if (e->map[t->x][i].data[1] == '1' &&
			e->map[t->x][i].data[0] == '1')
			break;
		e->map[t->x][i].data[4] = '1';
	}
	t->status = 1;
	t->start = clock();
}

void do_timing_entity(t_env *e, t_timer **t)
{
	int i = 0;
	clock_t now = clock();

	while (t[i] != NULL) {
		if (t[i]->status == 0 && (now - t[i]->start) > 300) {
			bomb_explose(e, t[i]);
		}
		if (t[i]->status == 1 && (now - t[i]->start) > 100) {
//			clean_fire(e, t);
		}
		i++;
	}
}