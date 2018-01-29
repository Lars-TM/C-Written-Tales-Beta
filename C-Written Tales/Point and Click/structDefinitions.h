// WARNING: SHARING DATA GLOBALLY IS BAD PRACTICE

#ifndef GLOBAL_H
#define GLOBAL_H

#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

//Any type definitions needed
typedef struct
{
  int x, y;
  int imgID;
} Person;

typedef struct{
	int id;
    int xPosition;
	int yPosition;
	int width;
	int height;
	int imgID;
} renderedObject;

typedef struct{
	int id;
		int xPosition;
	int yPosition;
	int width;
	int height;
	int imgID;

	bool clickable;
	int clickCount;
	int EventId;

	bool interactiveWithObject;
	int idOfNeededObjectToInteract;

	bool OnlyUsableWhenNear;

	int InteractionEventID;
	int InteractionEventCount;
} interactiveRenderedObject;

typedef struct{
	int id;
	int xPosition;
	int yPosition;
	int width;
	int height;
	int imgID;

	bool clickable;
	int clickCount;
	int EventId;

	bool ableToCraft;
	int idOfNeededObjectToCraft;
	bool OnlyUsableWhenNear;

	int CraftEventID;
	int CraftEventCount;
} collectibleObject;




typedef struct
{
  //Players
  Person person;

  //Room
  int currentRoom;

  //Time
  int time;

  //Input
  int acceptInput;
  int acceptOnlyNumberInput;
  int acceptNoArrowInput;

  //Riddle
  int DialogueAnswer;

  //objectsArrays
  renderedObject renderedObjects[300];
  interactiveRenderedObject interactiveRenderedObjects[250];
  collectibleObject collectibleObjects[100];

  //ObjectsOnGameDisplay
  int countObjectsIn_Ways[10];
  int Ways[10][100];
  int countObjectsIn_Background[10];
  int Background[10][100];
  int countObjectsIn_LayerTwo[10];
  int LayerTwo[10][100];
  int countObjectsIn_LayerThree[10];
  int LayerThree[10][100];
  int countObjectsIn_LayerFour[10];
  int LayerFour[10][100];
  int countObjectsIn_LayerFive[10];
  int LayerFive[10][100];
  int countObjectsIn_Foreground[10];
  int Foreground[10][100];
  int countObjectsIn_Blackscreen[10];
  int Blackscreen[10][100];

  //ObjectsInInventory
  int countObjectsInInventory;
  int objectsInInventory[100];

  //PositionInInventory
  int PositionInInventory;

  //Item mounted on Mouse
  int idOfObjectMountedOnMouse;

  //Animations
  int countObjectsIn_LoopAnimations;
  int LoopAnimations[50][2];
  int countObjectsIn_OneTimeAnimations;
  int OneTimeAnimations[50][2];

  //Images
  SDL_Texture *textures[200];
  SDL_Window *window;
  SDL_Renderer *renderer;

  //Audio
  //The music that will be played
  Mix_Music *gMusic[20];

    //The sound effects that will be used
  Mix_Chunk *gSounds[200];

  //Text
  TTF_Font *fontToUse;
  char TextToShow[200];


  //Window
  int WINDOW_WIDTH;
  int WINDOW_HEIGHT;
  int GAME_WINDOW_BOTTOM;
  int PERSON_HEIGHT;
  int PERSON_WIDTH;

  //Menu
  int actualGame;

} GameState;


typedef struct
{
  GameState *game;
  pthread_t thread_handle;
} passToThreadStruct_Event;

/*#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT (int)(((double)WINDOW_WIDTH/(double)12)*(double)8)
#define GAME_WINDOW_BOTTOM (int)(((double)WINDOW_WIDTH/(double)75)*(double)9)
#define PERSON_HEIGHT                 (int)(double)WINDOW_WIDTH/(double)4 //M Change
#define PERSON_WIDTH                  (int)(double)WINDOW_WIDTH/(double)8*/

#define NUMBER_OF_IMAGES_TO_LOAD 87
#define NUMBER_OF_BACKGROUNDMUSICS_TO_LOAD 4
#define NUMBER_OF_SOUNDS_TO_LOAD 1
#define ANIMATION_SPEED_CHARACKTER 8
#define ANIMATION_SPEED 20
#define NEARAREAEXTENTIONX 60
#define NEARAREAEXTENTIONY 60
#define MOVEVELOCITY 10



#endif
