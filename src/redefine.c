#include "redefine.h"

extern void flushInputs(void);
extern int getSingleInput(void);
extern void drawString(char *, int, int, TTF_Font *, int, int);

void drawRedefine(void);

void doRedefine()
{
	int key = -1;
	
	if (strlen(redefine.redefineString) == 0)
	{
		switch (redefine.redefineIndex)
		{
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
	
	while (key == -2)
	{
		key = getSingleInput();
		
		drawRedefine();
	}
	
	switch (redefine.redefineIndex)
	{
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
	
	if (redefine.redefineIndex == 5)
	{
		redefine.redefineIndex = 0;
		
		game.status = IN_GAME;
	}
}

void drawRedefine()
{
	/* Blank the screen */
	
	SDL_FillRect(game.screen, NULL, 0);
	
	/* Draw the redefine string */
	
	drawString(redefine.redefineString, 0, 0, game.font, 1, 1);
	
	/* Update the buffer */

	SDL_Flip(game.screen);
	
	/* Sleep briefly */
	
	SDL_Delay(1);
}
