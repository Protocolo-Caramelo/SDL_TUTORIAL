/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_mixer.h>

#include "../common.h"

#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSound(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

	music = NULL;

	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void stopMusic(void)
{
	Mix_HaltMusic();
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

void setSoundVolume(int volume)
{
	volume = MIN(MAX(0, volume), MIX_MAX_VOLUME);

	Mix_Volume(-1, volume);
}

void setMusicVolume(int volume)
{
	volume = MIN(MAX(0, volume), MIX_MAX_VOLUME);

	Mix_VolumeMusic(volume);
}

static void loadSounds(void)
{
}
