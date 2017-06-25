#ifndef __SERVER_H__
# define __SERVER_H__

# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <math.h>

# define FD_FREE			0
# define FD_CLIENT			1
# define FD_SERVER			2
# define BUFF_SIZE			3000
# define MAX_PLAYER			5
/* 4 + 1 for server fd in player tab */
# define MAX_TIMER			120
// TODO improve timer stuct
# define MAP_SIZE			15

# define PRES				100
# define PLAYER_SPEED		5
# define PLAYER_MAX_LIFE	1
# define PLAYER_MAX_AMMO	5
# define PLAYER_RELOAD_TIME	10
# define BOMB_TIMER			2500
# define FIRE_TIMER			300

typedef struct	s_player
{
	int			x;
	int			y;
	int			fd;
	int			dir;
	int			type;
	int			life;
	int			ammo;
	int			speed;
	int			frags;
	int			reload;
	int			connected;
}				t_player;

typedef struct	s_map
{
	char		*data;
}				t_map;

typedef struct	s_info
{
	int			status;
	int			winner;
	int			max_player;
	int			throw_bomb;
	int			player_boost;
}				t_info;

typedef struct	s_timer
{
	int			x;
	int			y;
	int			nb;
	clock_t		start;
	int			status;
}				t_timer;

typedef struct	s_env
{
	int			port;
	int			fd_max;
	fd_set		fd_read;
	fd_set		fd_write;
	t_map		**map;
	t_info		*info;
	t_timer		**timer;
	t_player	**player;
}				t_env;

typedef struct	s_request
{
	int			nb;
	int			dir;
	int			fire;
	int			ckecksum;
}				t_request;

typedef struct	s_response
{
	t_map		**map;
	t_info		*info;
	t_player	**player;
}				t_response;

int				send_response(t_env *, t_player *);
t_request		*unserialize_request(char *buffer);
t_map			**load_map();

void			do_player_move(t_env *, t_request *, int);
void			do_player_throw_bomb(t_env *, t_request *, int);
void			do_timing_entity(t_env *);
void			do_player_get_beer_boosted(t_env *, t_player *);

void			clean_server(t_env *);
void			free_map(t_map **);

#endif /* __SERVER_H__ */
