#ifndef AUDIO_H
#define AUDIO_H

#include "structDefinitions.h"

extern void startMusic(GameState *game, int musicID);

extern void stopMusic(GameState *game);

extern void playSound(GameState *game, int soundID, int looops);

#endif


