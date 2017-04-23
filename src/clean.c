#include "clean.h"

void clean_client(t_game *g)
{
	/* free sprites and map */
	free_sprites();
	free_map(g->map);

	/* Close the font */
	close_font(g->font);

	/* Close the joystick */
	if (g->joystick != NULL)
		SDL_JoystickClose(g->joystick);

	/* Close SDL_TTF */
	TTF_Quit();

	/* Shut down SDL */
	SDL_DestroyRenderer(g->renderer);
	SDL_DestroyWindow(g->screen);
	SDL_Quit();
}
