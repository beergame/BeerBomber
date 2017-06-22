#include "player.h"

int pres_co(int co)
{
	return round(co / PRES);
}

void player_move(t_env *e, int i, int x, int y)
{
	e->player[i]->x = x;
	e->player[i]->y = y;
}

int no_player_here(t_env *e, int x, int y)
{
	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (e->player[i]->connected == 1) {
			if (x == pres_co(e->player[i]->x) &&
				y == pres_co(e->player[i]->y)) {
				return (0);
			}
		}
	}

	return (1);
}

void do_player_move(t_env *e, t_request *req, int i) {
	if (e->player[i] != NULL) {
		int x = pres_co(e->player[i]->x);
		int y = pres_co(e->player[i]->y);
		int xt = e->player[i]->x % PRES;
		int yt = e->player[i]->y % PRES;
		if (req->dir) {
			if (req->dir == 1 &&
				((y > 1 && (e->map[x][y - 1].data[1] == '0') &&
				  (e->map[x][y - 1].data[3] != '1')) || yt) &&
				no_player_here(e, x, y - 1))
				player_move(e, i, e->player[i]->x, e->player[i]->y - e->player[i]->speed);
			else if (req->dir == 2 &&
					 ((y < MAP_SIZE - 2 && (e->map[x][y + 1].data[1] == '0')
					   && (e->map[x][y + 1].data[3] != '1')) || yt) &&
					 no_player_here(e, x, y + 1))
				player_move(e, i, e->player[i]->x, e->player[i]->y + e->player[i]->speed);
			else if (req->dir == 3 && ((x > 1 && (e->map[x - 1][y].data[1] == '0') &&
					(e->map[x - 1][y].data[3] != '1')) || xt) &&
					 no_player_here(e, x - 1, y))
				player_move(e, i, e->player[i]->x - e->player[i]->speed, e->player[i]->y);
			else if (req->dir == 4 &&
					 ((x < MAP_SIZE - 2 && (e->map[x + 1][y].data[1] == '0') &&
							 (e->map[x + 1][y].data[3] != '1')) || xt) &&
					 no_player_here(e, x + 1, y))
				player_move(e, i, e->player[i]->x + e->player[i]->speed, e->player[i]->y);
		}
	}
}

void throw_bomb(t_env *e, t_player *p)
{
	int i = -1;
	clock_t now = clock();
	t_timer *t = malloc(sizeof(t_timer));

	t->x = pres_co(p->x);
	t->y = pres_co(p->y);
	t->status = 0;
	t->start = now;
	t->nb = p->fd;
	e->map[pres_co(p->x)][pres_co(p->y)].data[3] = '1';

	while (e->timer[++i] != NULL);
	e->timer[i] = t;
}

void do_player_throw_bomb(t_env *e, t_request *r, int i)
{
	t_player *p = e->player[i];
	p->reload--;
	if (p->reload < 0) {
		p->reload = 0;
	}
	if (r->fire == 1 && p->ammo > 0 &&
		e->map[pres_co(p->x)][pres_co(p->y)].data[3] != '1' &&
		e->map[pres_co(p->x)][pres_co(p->y)].data[4] == '0' &&
		p->reload <= 0) {
		throw_bomb(e, p);
		e->info->throw_bomb = 1;
		p->ammo--;
		p->reload = PLAYER_RELOAD_TIME;
	}
}
