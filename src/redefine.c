#include "redefine.h"

int doRedefine(Game *game)
{
	int key = -1;

	if (strlen(redefine.redefineString) == 0) {
		switch (redefine.redefineIndex) {
			case 0:
				strcpy(redefine.redefineString, "Press key for Left");
				break;

			case 1:
				strcpy(redefine.redefineString, "Press key for Right");
				break;

			case 2:
				strcpy(redefine.redefineString, "Press key for Up");
				break;

			case 3:
				strcpy(redefine.redefineString, "Press key for Down");
				break;

			default:
				strcpy(redefine.redefineString, "Press key for Fire");
				break;
		}
	}

	flushInputs();

	key = -2;

	while (key == -2) {
		key = getSingleInput();
		if (key == 1)
			return (1);

		drawRedefine(game);
	}

	switch (redefine.redefineIndex) {
		case 0:
			customControl.left = key;
			break;

		case 1:
			customControl.right = key;
			break;

		case 2:
			customControl.up = key;
			break;

		case 3:
			customControl.down = key;
			break;

		default:
			customControl.fire = key;
			break;
	}

	redefine.redefineIndex++;

	redefine.redefineString[0] = '\0';

	if (redefine.redefineIndex == 5) {
		redefine.redefineIndex = 0;
		game->status = IN_GAME;
	}

	return (0);
}

void drawRedefine(Game *game)
{
	/* Blank the screen */

	SDL_RenderClear(game->renderer);

	/* Draw the redefine string */

	drawString(game, redefine.redefineString, 0, 0, game->font, 1, 1);

	/* Update the buffer */

	SDL_RenderPresent(game->renderer);

	/* Sleep briefly */

	SDL_Delay(1);
}
