#ifndef STRUCTS_H
# define STRUCTS_H

# include "defs.h"

typedef struct		s_map
{
	char			*data;
}					t_map;

typedef struct		s_control
{
	int				up;
	int				down;
	int				fire;
	int				left;
	int				right;
}					t_control;

typedef struct		s_player
{
	int				x;
	int				y;
	int				fd;
	int				dir;
	int				type;
	int				ammo;
	int				life;
	int				speed;
	int				frags;
	int				reload;
	int				connected;
}					t_player;

typedef struct		s_info
{
	int				status;
	int				winner;
	int				max_player;
	int				player_boost;
	int				throw_bomb;
}					t_info;

typedef struct		s_redefine
{
	int				i;
	char			buffer[255];
}					t_redefine;

typedef struct		s_sprite
{
	SDL_Texture		*image;
}					t_sprite;

typedef struct		s_sound
{
	Mix_Chunk		*effect;
}					t_sound;

typedef struct		s_game
{
	t_map			**map;
	t_info			*info;
	t_player		**player;
	t_control		*input;
	t_control		*control;
	t_redefine		*redefine;
	SDL_Window		*screen;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Joystick	*joystick;
	t_sound			sounds[8];
	Mix_Music		*music;
	clock_t			starter;
}					t_game;

typedef struct		s_request
{
	int				nb;
	int				dir;
	int				fire;
	int				ckecksum;
}					t_request;

#endif /* STRUCTS_H */
