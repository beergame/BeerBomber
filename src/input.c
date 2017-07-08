#include "input.h"

int get_input(t_game *game)
{
	int key;
	SDL_Event event;

	/* Loop through waiting messages and process them */

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			/* Closing the Window will exit the program */
			case SDL_QUIT:
				game->info->status = END_GAME;
				return (2);

			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
				if (key == game->control->left)
					game->input->left = 1;
				else if (key == game->control->right)
					game->input->right = 1;
				else if (key == game->control->up)
					game->input->up = 1;
				else if (key == game->control->down)
					game->input->down = 1;
				else if (key == game->control->fire)
					game->input->fire = 1;
				else if (key == SDLK_ESCAPE) {
					Mix_PlayChannel(-1, game->sounds[6].effect, 0);
					game->info->status = IN_REDEFINE;
				}
				break;

			case SDL_KEYUP:
				key = event.key.keysym.sym;
				if (key == game->control->left)
					game->input->left = 0;
				else if (key == game->control->right)
					game->input->right = 0;
				else if (key == game->control->up)
					game->input->up = 0;
				else if (key == game->control->down)
					game->input->down = 0;
				else if (key == game->control->fire)
					game->input->fire = 0;
				break;

			case SDL_JOYBUTTONDOWN:
				key = event.jbutton.button;
				if (key == game->control->left)
					game->input->left = 1;
				else if (key == game->control->right)
					game->input->right = 1;
				else if (key == game->control->up)
					game->input->up = 1;
				else if (key == game->control->down)
					game->input->down = 1;
				else if (key == game->control->fire)
					game->input->fire = 1;
				break;

			case SDL_JOYBUTTONUP:
				key = event.jbutton.button;
				if (key == game->control->left)
					game->input->left = 0;
				else if (key == game->control->right)
					game->input->right = 0;
				else if (key == game->control->up)
					game->input->up = 0;
				else if (key == game->control->down)
					game->input->down = 0;
				else if (key == game->control->fire)
					game->input->fire = 0;
				break;

//			case SDL_JOYAXISMOTION:
//				/* Horizontal movement */
//				if (event.jaxis.axis == 0) {
//					if (event.jaxis.value < -DEAD_ZONE)
//						game->input->left = 1;
//					else if (event.jaxis.value > DEAD_ZONE)
//						game->input->right = 1;
//					else {
//						game->input->left = 0;
//						game->input->right = 0;
//					}
//				}
//
//				/* Vertical movement */
//				if (event.jaxis.axis == 1) {
//					if (event.jaxis.value < -DEAD_ZONE) {
//						game->input->up = 1;
//					} else if (event.jaxis.value > DEAD_ZONE) {
//						game->input->down = 1;
//					} else {
//						game->input->up = 0;
//						game->input->down = 0;
//					}
//				}
//				break;
		}
	}

	return (0);
}

void flush_inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {}
}

int get_single_input()
{
	int key;
	SDL_Event event;

	key = -2;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return (1);

			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
				break;

//			case SDL_JOYAXISMOTION:
//				if (abs(event.jaxis.value) > DEAD_ZONE) {
//					key = -3;
//				}
//				break;

			case SDL_JOYBUTTONDOWN:
				key = event.jbutton.button;
				break;
		}
	}

	if (key == SDLK_ESCAPE)
		return (1);

	return key;
}
