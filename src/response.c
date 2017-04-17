#include "response.h"

char *serialize_response(t_response *res)
{
	char *buffer = malloc(BUFF_SIZE);

	sprintf(buffer, "%i:", res->infos.game_status);
	sprintf(buffer, "%i:", res->infos.nb_players);
	sprintf(buffer, "%i ", res->infos.winner_player);

	/* player 0 is server fd -> start at 1 */
	for (int i = 1; i < MAX_PLAYER; i++) {
		sprintf(buffer, "%i:", res->players[i]->x);
		sprintf(buffer, "%i:", res->players[i]->y);
		sprintf(buffer, "%i:", res->players[i]->ammo);
		sprintf(buffer, "%i:", res->players[i]->reload);
		sprintf(buffer, "%i:", res->players[i]->frags);
		sprintf(buffer, "%i:", res->players[i]->connected);
		sprintf(buffer, "%i:", res->players[i]->life);
		sprintf(buffer, "%i;", res->players[i]->speed);
	}
	sprintf(buffer, " ");

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			sprintf(buffer, "%s:", res->map[i][j].data);
		}
		sprintf(buffer, ";");
	}
	buffer[strlen(buffer) - 1] =  '\0';

	return (buffer);
}

int send_response(t_env *e, t_player *player)
{
	t_response res;
	char *buffer;

	res.players = e->players;
	res.map = e->map;
	res.infos = e->infos;

	buffer = serialize_response(&res);
	printf("server: %s\n", buffer);
	if (send(player->fd, buffer, strlen(buffer), 0) < 0) {
		puts("Send failed");
		return (0);
	}

	return (1);
}
