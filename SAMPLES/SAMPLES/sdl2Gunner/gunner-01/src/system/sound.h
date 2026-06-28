/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

void initSound(void);
void setSoundVolume(int vol);
void setMusicVolume(int vol);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);
void playSoundLoop(int id, int channel);
void stopChannel(int channel);
