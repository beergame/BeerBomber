#include "map_server.h"

t_map **load_server_map()
{
	t_map **tmp;

	if (!(tmp = malloc(MAP_SIZE * sizeof(t_map *))))
		return (NULL);
	for (int i = 0; i < MAP_SIZE; i++) {
		if (!(tmp[i] = malloc(MAP_SIZE * sizeof(t_map))))
			return (NULL);
		for (int j = 0; j < MAP_SIZE; j++) {
			tmp[i][j].data = strdup("00000000");
			if (i == 0 || j == 0 || i == MAP_SIZE - 1 ||
				j == MAP_SIZE - 1 || (!(i % 2) && !(j % 2))) {
				/* @ = 01000000 */
				tmp[i][j].data = "01000000";
			} else if (i != 1) {
				/* ` = 01100000 */
				tmp[i][j].data = "01100000";
			}
		}
	}

	return tmp;
}
