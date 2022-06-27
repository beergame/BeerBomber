#include "init.h"

int init_main(t_game *game)
{
	int joystick_count, btn_count;
	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Initialise SDL_TTF */
	if (TTF_Init() < 0) {
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		return (1);
	}
	/* Open a screen */
	game->screen = SDL_CreateWindow("BeerBomber", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_SetWindowIcon(game->screen, IMG_Load("gfx/icon/beerbomber.png"));
	/* Create Renderer SDL 2.0 */
	game->renderer = SDL_CreateRenderer(game->screen, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	game->info = malloc(sizeof(t_info));
	game->info->status = IN_REDEFINE;
	game->info->winner = 0;
	game->info->throw_bomb = 0;
	game->info->player_boost = 0;
	game->info->max_player = 1;
	game->redefine = malloc(sizeof(t_redefine));
	game->redefine->i = 0;
	game->redefine->buffer[0] = '\0';
	game->input = malloc(sizeof(t_control));
	game->control = malloc(sizeof(t_control));
	game->input->down = 0;
	game->input->up = 0;
	game->input->right = 0;
	game->input->left = 0;
	game->input->fire = 0;
	game->font = loadFont("font/blackWolf.ttf", 16);
	if (game->screen == NULL) {
		printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH,
			   SCREEN_HEIGHT, SDL_GetError());
		return (1);
	}
	/* Set the audio rate to 22050 */
	if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0) {
		printf("Could not open audio: %s\n", Mix_GetError());
		return (1);
	}
	/* Open the joystick */
	joystick_count = SDL_NumJoysticks();
	if (joystick_count != 0) {
		printf("Found %d joystick(s). Opening Joystick #0: %s\n",
			   joystick_count, SDL_JoystickName(0));
		game->joystick = SDL_JoystickOpen(0);
		btn_count = SDL_JoystickNumButtons(game->joystick);
		printf("Joystick has %d buttons\n", btn_count);
		printf("Joystick has %d axes\n", SDL_JoystickNumAxes(game->joystick));
	}
	load_all_sprites(game);
	load_all_sound(game);
	return (0);
}

void init_client(t_game *g)
{
	/* data clearing */
	g->starter = clock();
	g->map = load_map();
	g->player = malloc(MAX_PLAYER * sizeof(t_player *));
	for (int i = 0; i < MAX_PLAYER; i++) {
		if ((g->player[i] = malloc(sizeof(t_player))) == NULL)
			break ;
		g->player[i]->x = 0;
		g->player[i]->y = 0;
		g->player[i]->ammo = 0;
		g->player[i]->reload = 0;
		g->player[i]->frags = 0;
		g->player[i]->connected = 0;
		g->player[i]->life = 0;
		g->player[i]->speed = 0;
	}
	g->redefine->i = 0;
	g->redefine->buffer[0] = '\0';
	g->input->down = 0;
	g->input->up = 0;
	g->input->right = 0;
	g->input->left = 0;
	g->input->fire = 0;
}
