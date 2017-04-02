#include "input.h"

void getInput()
{
	int key;
	SDL_Event event;
	
	/* Loop through waiting messages and process them */
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			/*
			** Closing the Window will exit the program
			*/
			
			case SDL_QUIT:
				exit(0);
				break;
			
			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
				
				if (key == customControl.left)
				{
					input.left = 1;
				}
				
				else if (key == customControl.right)
				{
					input.right = 1;
				}
				
				else if (key == customControl.up)
				{
					input.up = 1;
				}
				
				else if (key == customControl.down)
				{
					input.down = 1;
				}
				
				else if (key == customControl.fire)
				{
					input.fire = 1;
				}
				
				else if (key == SDLK_ESCAPE)
				{
					game.status = IN_REDEFINE;
				}
				break;
			
			case SDL_KEYUP:
				key = event.key.keysym.sym;
				
				if (key == customControl.left)
				{
					input.left = 0;
				}
				
				else if (key == customControl.right)
				{
					input.right = 0;
				}
				
				else if (key == customControl.up)
				{
					input.up = 0;
				}
				
				else if (key == customControl.down)
				{
					input.down = 0;
				}
				
				else if (key == customControl.fire)
				{
					input.fire = 0;
				}
				break;
				
			case SDL_JOYBUTTONDOWN:
				key = event.jbutton.button;
				
				if (key == customControl.left)
				{
					input.left = 1;
				}
				
				else if (key == customControl.right)
				{
					input.right = 1;
				}
				
				else if (key == customControl.up)
				{
					input.up = 1;
				}
				
				else if (key == customControl.down)
				{
					input.down = 1;
				}
				
				else if (key == customControl.fire)
				{
					input.fire = 1;
				}
				break;
				
			case SDL_JOYBUTTONUP:
				key = event.jbutton.button;
				
				if (key == customControl.left)
				{
					input.left = 0;
				}
				
				else if (key == customControl.right)
				{
					input.right = 0;
				}
				
				else if (key == customControl.up)
				{
					input.up = 0;
				}
				
				else if (key == customControl.down)
				{
					input.down = 0;
				}
				
				else if (key == customControl.fire)
				{
					input.fire = 0;
				}
				break;
				
			case SDL_JOYAXISMOTION:
				/* Horizontal movement */
				
				if (event.jaxis.axis == 0)
				{
					if (event.jaxis.value < -DEAD_ZONE)
					{
						input.left = 1;
					}

					else if (event.jaxis.value > DEAD_ZONE)
					{
						input.right = 1;
					}

					else
					{
						input.left = 0;
						input.right = 0;
					}
				}
				
				/* Vertical movement */
				
				if (event.jaxis.axis == 1)
				{
					if (event.jaxis.value < -DEAD_ZONE)
					{
						input.up = 1;
					}

					else if (event.jaxis.value > DEAD_ZONE)
					{
						input.down = 1;
					}

					else
					{
						input.up = 0;
						input.down = 0;
					}
				}
				break;
		}
	}
}

void flushInputs()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {}
}

int getSingleInput()
{
	int key;
	SDL_Event event;

	key = -2;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
			break;

			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
			break;
			
			case SDL_JOYAXISMOTION:
				if (abs(event.jaxis.value) > DEAD_ZONE)
				{
					key = -3;
				}
			break;

			case SDL_JOYBUTTONDOWN:
				key = event.jbutton.button;
			break;
		}
	}
	
	if (key == SDLK_ESCAPE)
	{
		exit(0);
	}

	return key;
}
