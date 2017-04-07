#ifndef STRUCTS_H
# define STRUCTS_H

# include "defs.h"

struct				MapCase;

typedef struct		Entity
{
	int				speed;
	int				x;
	int				y;
	int				life;
	int				ammo;
	SDL_Surface		*sprite;

	void			(*action)(struct MapCase **, struct Entity *);

	void			(*draw)(SDL_Surface *, int, int);
} Entity;

typedef struct		MapCase
{
	Entity			*player;
	Entity			*bomb;
	Entity			*block;
	Entity			*fire;
	SDL_Surface		*sprite;
} MapCase;

typedef struct		Game
{
	int				score;
	int				status;
	MapCase			**map;
	SDL_Surface		*screen;
	TTF_Font		*font;
	SDL_Joystick	*joystick;
}					Game;

typedef struct		Sprite
{
	SDL_Surface		*image;
}					Sprite;

typedef struct		Sound
{
	Mix_Chunk		*effect;
}					Sound;

typedef struct		Control
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				fire;
}					Control;

typedef struct		Redefine
{
	int				redefineIndex;
	char			redefineString[255];
}					Redefine;

#endif /* STRUCTS_H */
