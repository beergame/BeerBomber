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


void do_player_throw_bomb(t_env *e, t_request *req)
{
	t_player *player = e->players[req->player_nb];
	player->reload--;
	if (player->reload < 0) {
		player->reload = 0;
	}
	if (req->fire == 1 && player->ammo > 0 &&
		e->map[player->x][player->y].data[3] != '1' &&
		e->map[player->x][player->y].data[4] != '1' &&
		player->reload <= 0) {
//		addBomb(map, player->x, player->y);
		player->ammo--;
		player->reload = PLAYER_RELOAD_TIME;
	}
}
