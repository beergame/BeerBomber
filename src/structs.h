#ifndef STRUCTS_H
# define STRUCTS_H

# include "defs.h"

struct				MapCase;
struct				Game;

typedef struct		Entity
{
	int				type;
	int				speed;
	int				x;
	int				y;
	int				life;
	int				ammo;
	int				reload;
	SDL_Texture		*sprite;

	void			(*action)(struct MapCase **, struct Entity *);

	void			(*draw)(struct Game *, SDL_Texture *, int, int);
} Entity;

typedef struct		MapCase
{
	SDL_Texture		*sprite;
	Entity			*player;
	Entity			*bomb;
	Entity			*block;
	Entity			*fire;
} MapCase;

typedef struct		Control
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				fire;
}					Control;

typedef struct		Game
{
	int				score;
	int				status;
	int				btn;
	MapCase			**map;
	Control			*customControl;
	Control			*input;
	SDL_Window		*screen;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Joystick	*joystick;
}					Game;

typedef struct		Sprite
{
	SDL_Texture		*image;
}					Sprite;

typedef struct		Sound
{
	Mix_Chunk		*effect;
}					Sound;

typedef struct		Redefine
{
	int				redefineIndex;
	char			redefineString[255];
}					Redefine;

#endif /* STRUCTS_H */
