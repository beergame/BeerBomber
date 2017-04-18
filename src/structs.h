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

typedef struct	s_map
{
	char		*data;
}				t_map;

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
