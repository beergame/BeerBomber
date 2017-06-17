#include "request.h"

t_request *unserialize_request(char *buffer)
{
	t_request *tmp = malloc(sizeof(t_request));
	char **request;

	request = my_str_to_wordtab(buffer, ':');
	tmp->nb = atoi(request[0]);
	tmp->dir = atoi(request[1]);
	tmp->fire = atoi(request[2]);
	tmp->ckecksum = atoi(request[3]);

	return (tmp);
}

int send_serialize_request(t_request *req, int sock)
{
	char request[BUFF_SIZE] = "";
	char buff[3];

	sprintf(buff, "%i:", req->nb);
	strcat(request, buff);
	sprintf(buff, "%i:", req->dir);
	strcat(request, buff);
	sprintf(buff, "%i:", req->fire);
	strcat(request, buff);
	sprintf(buff, "%i", req->ckecksum);
	strcat(request, buff);

	request[strlen(request)] =  '\0';

//	printf("client: request: %s \n", request);
	if (send(sock, request, strlen(request), 0) < 0) {
		printf("Send failed\n");
		return (1);
	}
	return (0);
}
