#include "player.h"

int pres_co(int co, int i)
{
	double tmp = co;

	tmp = tmp / PRES;

	return (i) ? (int)(tmp + 0.49) : (int)(tmp - 0.49);
}

void player_move(t_env *e, int i, int x, int y)
{
	e->player[i]->x = x;
	e->player[i]->y = y;
}

void do_player_move(t_env *e, t_request *req, int i) {
	if (e->player[i] != NULL && e->player[i]->life > 0) {
		int xp = pres_co(e->player[i]->x, 1);
		int xm = pres_co(e->player[i]->x, 0);
		int yp = pres_co(e->player[i]->y, 1);
		int ym = pres_co(e->player[i]->y, 0);

		if (req->dir) {
			if (req->dir == 1 && e->map[xp][yp - 1].data[1] == '0')
				player_move(e, i, e->player[i]->x, e->player[i]->y - e->player[i]->speed);
			else if (req->dir == 2 && e->map[xp][ym + 1].data[1] == '0')
				player_move(e, i, e->player[i]->x, e->player[i]->y + e->player[i]->speed);
			else if (req->dir == 3 && e->map[xp - 1][yp].data[1] == '0')
				player_move(e, i, e->player[i]->x - e->player[i]->speed, e->player[i]->y);
			else if (req->dir == 4 && e->map[xm + 1][yp].data[1] == '0')
				player_move(e, i, e->player[i]->x + e->player[i]->speed, e->player[i]->y);
		}
	}
}

void throw_bomb(t_env *e, t_player *p)
{
	int i = -1;
	clock_t now = clock();
	t_timer *t = malloc(sizeof(t_timer));

	t->x = pres_co(p->x, 1);
	t->y = pres_co(p->y, 1);
	t->status = 0;
	t->start = now;
	t->nb = p->fd;
	e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[3] = '1';

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
		e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[1] == '0' &&
		e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[3] != '1' &&
		e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[4] == '0' &&
		p->reload <= 0 && p->life > 0) {
		throw_bomb(e, p);
		e->info->throw_bomb = 1;
		p->ammo--;
		p->reload = PLAYER_RELOAD_TIME;
	}
}


void do_player_get_beer_boosted(t_env *e, t_player *p)
{
	if (e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[5] == '1') {
		p->ammo += 5;
		e->info->player_boost = 1;
		e->map[pres_co(p->x, 1)][pres_co(p->y, 1)].data[5] = '0';
	}
}
