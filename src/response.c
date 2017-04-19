#include "response.h"

int serialize_response(t_response *res, int sock)
{
	char response[BUFF_SIZE] = "";
	char buff[10];

	sprintf(buff, "%i:", res->info->status);
	strcat(response, buff);
	sprintf(buff, "%i:", res->info->playermax);
	strcat(response, buff);
	sprintf(buff, "%i ", res->info->winner);
	strcat(response, buff);

	/* player 0 is server fd -> start at 1 */
	for (int i = 1; i < 2; i++) {
		sprintf(buff, "%i:", res->player[i]->x);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->y);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->ammo);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->reload);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->frags);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->connected);
		strcat(response, buff);
		sprintf(buff, "%i:", res->player[i]->life);
		strcat(response, buff);
		sprintf(buff, "%i;", res->player[i]->speed);
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

	res.player = e->player;
	res.map = e->map;
	res.info = e->info;

	return (serialize_response(&res, player->fd));
}
