#include "map_server.h"

t_map **load_map()
{
	t_map **tmp;

	if (!(tmp = malloc(MAP_SIZE * sizeof(t_map *))))
		return (NULL);
	for (int i = 0; i < MAP_SIZE; i++) {
		if (!(tmp[i] = malloc(MAP_SIZE * sizeof(t_map))))
			return (NULL);
		for (int j = 0; j < MAP_SIZE; j++) {
			/* 00000000 map vide */
			if (i == 0 || j == 0 || i == MAP_SIZE - 1 ||
				j == MAP_SIZE - 1 || (!(i % 2) && !(j % 2))) {
				/* 11000000 terrain indestructible */
				tmp[i][j].data = strdup("11000000");
			} else if ((i > 2 || j > 2) && (i < 12 || j < 12) &&
					(i > 2 || j < 12) && (i < 12 || j > 2)) {
				if  ((i % 3) || (j % 3)) {
					/* 01000000 terrain destructible */
					tmp[i][j].data = strdup("01000000");
				} else {
					/* 01000000 terrain destructible + bonus */
					tmp[i][j].data = strdup("01000100");
				}
			} else {
				tmp[i][j].data = strdup("00000000");
			}
		}
	}

	return tmp;
}

void free_map(t_map **map)
{
	for (int i = 0; i < MAP_SIZE; i++) {
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}
