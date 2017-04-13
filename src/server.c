#include "server.h"

void *serverBeerBomber(void *arg)
{
	printf("Nous sommes dans le thread server.\n");

	/* Pour enlever le warning */
	(void) arg;
	pthread_exit(NULL);
}
