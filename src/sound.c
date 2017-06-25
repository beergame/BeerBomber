#include "sound.h"

void load_all_sound(t_game *g)
{
	g->music = Mix_LoadMUS("gfx/scratch/music.wav");
	g->sounds[0].effect = Mix_LoadWAV("gfx/scratch/bomb_set.wav");
	g->sounds[1].effect = Mix_LoadWAV("gfx/scratch/bomb_set.wav");
	g->sounds[2].effect = Mix_LoadWAV("gfx/scratch/pause.wav");
	g->sounds[3].effect = Mix_LoadWAV("gfx/scratch/confirm.wav");
	g->sounds[4].effect = Mix_LoadWAV("gfx/scratch/out.wav");
	g->sounds[5].effect = Mix_LoadWAV("gfx/scratch/explose.wav");
	g->sounds[6].effect = Mix_LoadWAV("gfx/scratch/select.wav");
	g->sounds[7].effect = Mix_LoadWAV("gfx/scratch/walk.wav");
}

void free_sound(t_game *g)
{
	int i;

	/* Loop through the sound and clear it */
	for (i = 0; i < 8; i++) {
		if (g->sounds[i].effect != NULL) {
			Mix_FreeChunk(g->sounds[i].effect);
		}
	}
	Mix_FreeMusic(g->music);
}
