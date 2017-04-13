#include "client.h"

void *clientBeerBomber(void *arg)
{
	printf("Nous sommes dans le thread client.\n");

	/* Pour enlever le warning */
	(void) arg;
	pthread_exit(NULL);
}
