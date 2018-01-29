#ifndef DATA_H
#define DATA_H

//Any type definitions needed
extern void sleep_ms(int milliseconds);

extern int *buffercurrentlyOnDisplay;
extern int **currentlyOnDisplay;
extern int *bufferAllowedToWalkHere;
extern int **AllowedToWalkHere;

extern char imgSource[100][100];
extern char musicSource[100][100];
extern char soundSource[150][100];
extern int animationArray[100][15];
extern char riddles[50][2][200];
extern char texts[200][200];
extern char questions[200][200];
extern int letEmSpeakArray[200][3];

extern GameState *GAME;


extern void* handleEventId(void* parameter);
extern void loadBeginning(GameState *game);
extern void startEvent(GameState *game, int eventID, int clickCount, int objectID);

#endif


