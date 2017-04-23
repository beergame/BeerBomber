#include "bomb.h"

void fire_action_on_bush(t_env *e)
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

void fire_action_on_player(t_env *e)
{
	t_player **p = e->player;

	for (int i = 0; i < MAX_PLAYER; ++i) {
		if (p[i]->connected == 1 &&
			e->map[p[i]->x][p[i]->y].data[4] == '1') {
			p[i]->life--;
			if (p[i]->life == 0) {
				p[i]->x = 0;
				p[i]->y = 0;
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
	fire_action_on_bush(e);
	fire_action_on_player(e);
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
