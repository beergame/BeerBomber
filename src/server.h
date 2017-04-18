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

# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define MAX_FD 255
# define BUFF_SIZE 3000
# define MAX_PLAYER 4
# define MAP_SIZE 15

# define PLAYER_SPEED 13
# define PLAYER_MAX_LIFE 2
# define PLAYER_MAX_AMMO 100
# define PLAYER_RELOAD_TIME 9
# define BOMB_LIFETIME 150
# define FIRE_LIFETIME 20

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

typedef struct	s_timer
{
	int			x;
	int			y;
	int			status;
	int			player_nb;
	clock_t		start;
}				t_timer;

typedef struct	s_env
{
	int			port;
	fd_set		fd_write;
	fd_set		fd_read;
	int			fd_max;
	t_player	**players;
	t_map		**map;
	t_info		infos;
	t_timer		**timers;
}				t_env;

typedef struct	s_request
{
	int			player_nb;
	int			dir;
	int			fire;
	int			ckecksum;
}				t_request;

typedef struct	s_response
{
	t_player	**players;
	t_map		**map;
	t_info		infos;
}				t_response;

t_map			**load_server_map();
t_request		*unserialize_request(char *buffer);
int				send_response(t_env *, t_player *);

void			do_player_move(t_env *, t_request *);
void			do_player_throw_bomb(t_env *, t_request *);

#endif /* __SERVER_H__ */
