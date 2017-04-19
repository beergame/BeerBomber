#ifndef STRUCTS_H
# define STRUCTS_H

# include "defs.h"

struct				s_map_case;
struct				s_game;

typedef struct		s_entity
{
	int				type;
	int				speed;
	int				x;
	int				y;
	int				life;
	int				ammo;
	int				reload;
	SDL_Texture		*sprite;

	void			(*action)(struct s_map_case **, struct s_entity *);

	void			(*draw)(struct s_game *, SDL_Texture *, int, int);
}					t_entity;

//typedef struct		s_map_case
//{
//	t_entity		*player;
//	t_entity		*bomb;
//	t_entity		*block;
//	t_entity		*fire;
//}					t_map_case;

typedef struct		s_map
{
	char			*data;
}					t_map;

typedef struct		s_control
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				fire;
}					t_control;

typedef struct		s_game
{
	int				score;
	int				status;
	int				btn;
	t_map			**map;
	t_control		*control;
	t_control		*input;
	SDL_Window		*screen;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Joystick	*joystick;
}					t_game;

typedef struct		s_sprite
{
	SDL_Texture		*image;
}					t_sprite;

typedef struct		Sound
{
	Mix_Chunk		*effect;
}					Sound;

typedef struct		s_redefine
{
	int				i;
	char			buffer[255];
}					t_redefine;

typedef struct		s_request
{
	int				player_nb;
	int				dir;
	int				fire;
	int				ckecksum;
}					t_request;

typedef struct	s_player
{
	int			fd;
	int			type;
	int			connected;
	int			speed;
	int			x;
	int			y;
	int			life;
	int			ammo;
	int			reload;
	int			frags;
}				t_player;

typedef struct	s_info
{
	int			game_status;
	int			nb_players;
	int			winner_player;
}				t_info;

typedef struct s_response
{
	t_player	**players;
	t_map		**map;
	t_info		infos;
}				t_response;

#endif /* STRUCTS_H */
