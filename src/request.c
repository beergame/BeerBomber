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
