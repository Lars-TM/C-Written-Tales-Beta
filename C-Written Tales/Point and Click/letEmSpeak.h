#ifndef LETEMSPEAK_H
#define LETEMSPEAK_H
#include <pthread.h>
#include "structDefinitions.h"

//Any type definitions needed
extern void addTextToShow(GameState *game, char text[200]);

extern void deleteTextToShow(GameState *game);

extern void showText(GameState *game, char text[200]);

extern void letEmSpeak(GameState *game, int letEmSpeakId);

extern void drawTextLayer(GameState *game);

#endif
