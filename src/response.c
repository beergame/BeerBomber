#include "response.h"

int serialize_response(t_response *res, int sock)
{
	char response[BUFF_SIZE] = "";
	char buff[10];

	sprintf(buff, "%i:", res->infos.game_status);
	strcat(response, buff);
	sprintf(buff, "%i:", res->infos.nb_players);
	strcat(response, buff);
	sprintf(buff, "%i ", res->infos.winner_player);
	strcat(response, buff);

	/* player 0 is server fd -> start at 1 */
	for (int i = 1; i < 2; i++) {
		sprintf(buff, "%i:", res->players[i]->x);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->y);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->ammo);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->reload);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->frags);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->connected);
		strcat(response, buff);
		sprintf(buff, "%i:", res->players[i]->life);
		strcat(response, buff);
		sprintf(buff, "%i;", res->players[i]->speed);
		strcat(response, buff);
	}
	sprintf(buff, " ");
	strcat(response, buff);

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			sprintf(buff, "%s:", res->map[i][j].data);
			strcat(response, buff);
		}
		sprintf(buff, ";");
		strcat(response, buff);
	}

	response[strlen(response)] =  '\0';
	printf("server: response: %s\n", response);
	if (send(sock, response, strlen(response), 0) < 0) {
		puts("Send failed");
		return (0);
	}

	return (1);
}

int send_response(t_env *e, t_player *player)
{
	t_response res;

	res.players = e->players;
	res.map = e->map;
	res.infos = e->infos;

	return (serialize_response(&res, player->fd));
}
