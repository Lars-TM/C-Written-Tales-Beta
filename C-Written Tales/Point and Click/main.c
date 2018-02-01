#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "structDefinitions.h"
#include "dataOperations.h"
#include "data.h"
#include "render.h"
#include "customOnClickEvent.h"
#include "extras.h"

int  xPosition;
int  yPosition;
int test = 0;
int done = 1;

int checkIfMoveAllowed(GameState *game, int x, int y, int widthOfObject, int heightOfObject, int xMove, int yMove)
{
  /*printf("WINDOWWIDTH: %d\n", game->WINDOW_WIDTH);
    printf("X: %d\n", x);
    printf("y: %d\n", y);
    printf("PERSON_WIDTH: %d\n", game->PERSON_WIDTH);
    printf("PERSON_HEIGHT: %d\n", game->PERSON_HEIGHT);*/

    int hoehefuesse =heightOfObject/10;
    if (xMove > 0)
    {
        if (x + xMove + widthOfObject >= game->WINDOW_WIDTH)
        {
            //printf("%d +%d +%d = %d",x,xMove,widthOfObject,game->WINDOW_WIDTH);
            return 0;
        }
        else
        {
            for (int i=heightOfObject-hoehefuesse;i<heightOfObject;i++)
            {
                if(AllowedToWalkHere[x + xMove + widthOfObject][y+i] != 0)
                {
                    return 0;
                }
            }
        }
    }
    if (xMove < 0)
    {
        if (x + xMove < 0)
        {
          //  printf("2222");
            return 0;
        }
        else
        {
            for (int i=heightOfObject-hoehefuesse;i<heightOfObject;i++)
                {
                    if(AllowedToWalkHere[x + xMove][y+i] != 0)
                    {
                        return 0;
                    }
                }
        }
    }
    if (yMove > 0)
    {
        if (y + yMove + heightOfObject > game->GAME_WINDOW_BOTTOM)
        {
          //  printf("3333");
            return 0;
        }
        else
        {
            for (int j=0;j<widthOfObject;j++){
                if(AllowedToWalkHere[x + j][y + yMove + heightOfObject] != 0)
                {
                    return 0;
                }
            }
        }
    }
    if (yMove < 0)
    {
        if (y + yMove + heightOfObject - hoehefuesse < 0)
        {
          //  printf("4444");
            return 0;
        }
        else
        {
            for (int j=0;j<widthOfObject;j++){
                if(AllowedToWalkHere[x + j][y + yMove + heightOfObject-hoehefuesse] != 0)
                {
                    return 0;
                }
            }
        }
    }
    return(1);
}

//Game Logic - ShutDown
int shutDownGame(GameState *game, SDL_Window *window, SDL_Renderer *renderer){


     //Shutdown game and unload all memory
     printf("\n\n\nUnload images from memory...\n");
     for(int i = 0; i < NUMBER_OF_IMAGES_TO_LOAD; i++){
        SDL_DestroyTexture(game->textures[i]);
     }

    printf("Unload sounds from memory...\n");
    for(int i = 0; i < NUMBER_OF_SOUNDS_TO_LOAD; i++){
            Mix_FreeChunk(game->gSounds[i]);
            game->gSounds[i] = NULL;
     }

     printf("Unload Background musics from memory...\n");
     for(int i = 0; i < NUMBER_OF_BACKGROUNDMUSICS_TO_LOAD; i++){
            Mix_FreeMusic(game->gMusic[i]);
            game->gMusic[i] = NULL;
     }

     printf("Close font...\n");
     TTF_CloseFont(game->fontToUse);

     // Close and destroy the window
     printf("Destroy window...\n");
     SDL_DestroyWindow(window);
     printf("Destroy renderer...\n");
     SDL_DestroyRenderer(renderer);
     window = NULL;
     renderer = NULL;

     //Free Dynamically Allocated Memory
     printf("Free Dynamically Allocated Memory...\n");
     free(buffercurrentlyOnDisplay);
     free(currentlyOnDisplay);
     free(bufferAllowedToWalkHere);
     free(AllowedToWalkHere);

     // Clean up
     TTF_Quit();
     Mix_Quit();
     IMG_Quit();
     SDL_Quit();
     loadingDots();
     endOfGame();


     return 1;
}

//Game Logic - Load
int loadGame(GameState *game)
{
  printf("  \263   \263__Load Game...\n  \263      \263\n");

  //Load Images
  printf("  \263      \263__Load Images...\n");
  int imgSuccess = loadImagesInMemory(game);
  if(imgSuccess == 0){
    printf("  \263      \263   \263\n  \263      \263   \263__Failed To Load Images\n  \263      \263  \n");
  } else{
    printf("  \263      \263   \263\n  \263      \263   \263__Images loaded successfully\n  \263      \263  \n");
  }

  //Load music
  printf("  \263      \263__Load Audio...\n");
  int audioSuccess = loadAudioInMemory(game);
  if(audioSuccess == 0){
    printf("  \263         \263__Failed To Load Audio\n  \263\n  \263\n");
  } else{
    printf("  \263         \263__Audio loaded successfully\n  \263\n  \263\n");
  }


  initRuntimeArrays(game);

  for(int j=0; j < game->WINDOW_WIDTH; j++){
        for(int i = 0; i < game->WINDOW_HEIGHT; i++){
            currentlyOnDisplay[j][i] = 0;
        }
    }

  for(int j=0; j < game->WINDOW_WIDTH; j++){
        for(int i = 0; i < game->WINDOW_HEIGHT; i++){
            AllowedToWalkHere[j][i] = 0;
        }
    }

  game->acceptInput = 1;

  game->person.x = 525;
  game->person.y = 188;

  loadGameInMemory(game);

  if(imgSuccess == 1 && audioSuccess == 1){
        return 1;
  } else{
      return 0;
  }

}


//Input - Logic
int processEvents(SDL_Window *window, GameState *game)
{
    SDL_Event event;
    int       done   = 0;
    int       moveok = 1; //M change

    while (SDL_PollEvent(&event))
    {
        if(game->acceptOnlyNumberInput == 0){
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            printf("X:%d Y:%d \n", xPosition, yPosition);


            if (event.button.button == SDL_BUTTON_LEFT)
            {

            int leftBorderInventoryRightLeft = (int)(((double)game->WINDOW_WIDTH/(double)60)*(double)57);
            int rightBorderInventoryRightLeft = (int)(((double)game->WINDOW_WIDTH/(double)60)*(double)59);

            int upperBorderInventoryRight = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)137);
            int lowerBorderInventoryRight = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)145);

            int upperBorderInventoryLeft = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)149);
            int lowerBorderInventoryLeft = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)157);

            //InventoryRight
            if(xPosition >= leftBorderInventoryRightLeft && xPosition <= rightBorderInventoryRightLeft
               && yPosition >= upperBorderInventoryRight && yPosition <= lowerBorderInventoryRight){
                   if(game->PositionInInventory < game->countObjectsInInventory-1){
                    game->PositionInInventory++;
                   }
            }
            //InventoryLeft
            if(xPosition >= leftBorderInventoryRightLeft && xPosition <= rightBorderInventoryRightLeft
               && yPosition >= upperBorderInventoryLeft && yPosition <= lowerBorderInventoryLeft){
                if(game->PositionInInventory > 0){
                    game->PositionInInventory--;
                }
            }

            int leftBorderQuitSave = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)2);
            int rightBorderQuitSave = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)11);

            int upperBorderSave = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)137);
            int lowerBorderSave = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)146);

            int upperBorderQuit = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)149);
            int lowerBorderQuit = (int)(((double)game->WINDOW_WIDTH/(double)240)*(double)158);

            //Save
            if(xPosition >= leftBorderQuitSave && xPosition <= rightBorderQuitSave
               && yPosition >= upperBorderSave && yPosition <= lowerBorderSave){
                   startEvent(game, 57, 0, 0);
            }
            //Quit
            if(xPosition >= leftBorderQuitSave && xPosition <= rightBorderQuitSave
               && yPosition >= upperBorderQuit && yPosition <= lowerBorderQuit){
                shutDownGame(game, game->window,game->renderer);
            }


           //     printf("%d %d \n", xPosition, yPosition);
                customOnClickEvent(game, xPosition, yPosition, 0);
            }


            if (event.button.button == SDL_BUTTON_RIGHT)
            {
           //     printf("right\n");
                customOnClickEvent(game, xPosition, yPosition, 1);
            }

        }
        break;
        case SDL_MOUSEMOTION:
        {
            xPosition = event.motion.x;
            yPosition = event.motion.y;
        }
        break;
        case SDL_WINDOWEVENT_CLOSE:
        {
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done   = 1;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            //quit out of the game
            done = 1;
            break;
        }
    }

    if(game->acceptOnlyNumberInput == 1){


        switch (event.type)
        {
        case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = 1;
                    break;
                case SDLK_1:
                    game->DialogueAnswer = 1;
                    break;
                case SDLK_2:
                    game->DialogueAnswer = 2;
                    break;
                case SDLK_3:
                    game->DialogueAnswer = 3;
                    break;
                case SDLK_4:
                    game->DialogueAnswer = 4;
                    break;
                case SDLK_5:
                    game->DialogueAnswer = 5;
                    break;
                case SDLK_6:
                    game->DialogueAnswer = 6;
                    break;
                }
            }

        }
    }

    }
int direction = 0;
//1 Left
        //2 right
        //3 up
        //4 down

  if(game->acceptOnlyNumberInput == 0){
        if(game->acceptNoArrowInput == 0){

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        direction = 1;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        direction = 2;
    }
    if (state[SDL_SCANCODE_UP])
    {
        direction = 3;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        direction = 4;
    }
        }
  }


    int charXPos = game->person.x;
    int charYPos = game->person.y;
    int charWidth = game->PERSON_WIDTH;
    int charHeight = game->PERSON_HEIGHT;

    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        charXPos = (int)((double)charXPos*multiplier);
        charYPos = (int)((double)charYPos*multiplier);
        charWidth = (int)((double)charWidth*multiplier);
        charHeight = (int)((double)charHeight*multiplier);
    }


  if(direction == 1){
        moveok = checkIfMoveAllowed(game, charXPos, charYPos, charWidth, charHeight, -MOVEVELOCITY, 0);
        if (moveok == 1)
        {
            game->person.x -= MOVEVELOCITY;
            animateCharackter(game, 3);
        }
  }
  if(direction == 2){
        moveok = checkIfMoveAllowed(game, charXPos, charYPos, charWidth, charHeight, MOVEVELOCITY, 0);
        if (moveok == 1)
        {
            game->person.x += MOVEVELOCITY;
            animateCharackter(game, 1);
        }
  }
  if(direction == 3){
        moveok = checkIfMoveAllowed(game, charXPos, charYPos, charWidth, charHeight, 0, -MOVEVELOCITY);
        if (moveok == 1)
        {
            game->person.y -= MOVEVELOCITY;
            animateCharackter(game, 0);
        }
  }
  if(direction == 4){
        moveok = checkIfMoveAllowed(game, charXPos, charYPos, charWidth, charHeight, 0, +MOVEVELOCITY);
        if (moveok == 1)
        {
            game->person.y += MOVEVELOCITY;
            animateCharackter(game, 2);
        }
  }



    return done;
}


int main(int argc, char *argv[])
{
  GameState gameState;
  SDL_Window *window = NULL;                    // Declare a window
  SDL_Renderer *renderer = NULL;                // Declare a renderer


    /*int scannedVariable = 0;
    printf( "Which PixelWidth:\n");
            scanf ("%d",&scannedVariable);
            while (scannedVariable < 1 || 5000 < scannedVariable){
                printf("Not in Interval. Try another Number\n\n");
                printf( "Which PixelWidth:\n");
                scanf ("%d",&scannedVariable);
            }*/
    int  scannedVariable = 1200;

    gameState.WINDOW_WIDTH = scannedVariable;
    gameState.WINDOW_HEIGHT = (int)(((double)scannedVariable/(double)12)*(double)8);
    gameState.GAME_WINDOW_BOTTOM = (int)(((double)scannedVariable/(double)16)*(double)9);
    gameState.PERSON_HEIGHT = 300;
    gameState.PERSON_WIDTH = 150;


    printf( " Start Game...\n");
    printf( "  \263__Initialization\n  \263   \263\n");
   // printf( "    Initialization\n");
    //Initialize SDL2
    printf( "  \263   \263__Initialize SDL2...\n");
    if(SDL_Init(SDL_INIT_VIDEO) == 0){
        printf( "  \263   \263   \263__Initialization of SDL2 successful\n  \263   \263\n");
    } else{
        printf( "  \263   \263   \263__Failed to initialize SDL2\n  \263   \263\n");
    }

    //Initialize SDL2 - Audio
    printf( "  \263   \263__Initialize SDL2_Audio...\n");
    if(SDL_Init(SDL_INIT_AUDIO) == 0){
        printf( "  \263   \263   \263__Initialization of SDL2_Audio successful\n  \263   \263\n");
    } else{
        printf( "  \263   \263   \263__Failed to initialize SDL2_Audio\n  \263   \263\n");
    }

    //Initialize SDL2_Image
    //Initialize PNG loading
    printf( "  \263   \263__Initialize SDL2_Image...\n");
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "  \263   \263   \263__SDL_image could not initialize! SDL_image Error: %s\n  \263   \263\n", IMG_GetError() );
    }
    else{
        printf( "  \263   \263   \263__Initialization of SDL2_Image successful\n  \263   \263\n");
    }

    //Initialize SDL_mixer
    printf( "  \263   \263__Initialize SDL_Mixer...\n");
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        printf( "  \263   \263   \263__Failed to Initialize SDL_Mixer\n  \263   \263\n");
    } else{
        printf( "  \263   \263   \263__Initialization of SDL2_Mixer successful\n  \263   \263\n");
    }


    //Initialize SDL_TTF
    printf( "  \263   \263__Initialize SDL2_TTF...\n");
    if(TTF_Init() == 0){
        printf( "  \263      \263__Initialization of SDL2_TTF successful\n  \263\n  \263\n");
    } else{
        printf( "  \263      \263__Failed to initialize SDL2_TTF\n  \263\n  \263\n");
    }

    gameState.fontToUse = TTF_OpenFont("VT323-Regular.ttf", 23);


    //Allocate Memory For CurrentlyOnDisplay[][]
    int x_size=gameState.WINDOW_WIDTH;
    int y_size=gameState.WINDOW_HEIGHT;

    int i;
    /*int * */ buffercurrentlyOnDisplay = malloc(sizeof(int)*y_size*x_size);
    /*int ** */ currentlyOnDisplay = malloc(sizeof(int*)*x_size);
    for(i = 0; i<x_size; i++)
    currentlyOnDisplay[i]=&buffercurrentlyOnDisplay[i*y_size];

    //Allocate Memory For AllowedToWalkHere[][]
    /*int * */ bufferAllowedToWalkHere = malloc(sizeof(int)*y_size*x_size);
    /*int ** */ AllowedToWalkHere = malloc(sizeof(int*)*x_size);
    for(i = 0; i<x_size; i++)
    AllowedToWalkHere[i]=&bufferAllowedToWalkHere[i*y_size];




  //Create an application window with the following settings:
  printf( "  \263__Window Creation\n  \263   \263\n");
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            gameState.WINDOW_WIDTH,                               // width, in pixels
                            gameState.WINDOW_HEIGHT,                               // height, in pixels
                            0                                  // flags
                            );

  printf( "  \263   \263__Create Window...\n");
  if(window == NULL){
    printf( "  \263      \263__Failed to create Window\n  \263\n  \263\n");
  } else{
      printf( "  \263      \263__Created Window successfully\n  \263\n  \263\n");
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  gameState.renderer = renderer;
  gameState.window = window;

  printf( "  \263__Game Loading\n  \263   \263\n");
  if(loadGame(&gameState)){
   printf(" Game started successfully\n\n");
  } else{
      printf(" Failed to start Game properly\n\n");
  }

  printf("Size Variables:\n");
  printf("WINDOW_WIDTH: %d\n", gameState.WINDOW_WIDTH);
  printf("WINDOW_HEIGHT: %d\n", gameState.WINDOW_HEIGHT);
  printf("GAME_WINDOW_BOTTOM: %d\n", gameState.GAME_WINDOW_BOTTOM);
  printf("PERSON_HEIGHT: %d\n", gameState.PERSON_HEIGHT);
  printf("PERSON_WIDTH: %d\n\n", gameState.PERSON_WIDTH);

  loadMenu(&gameState);
  loadBeginning(&gameState);
   Mix_VolumeMusic(30);

  // The window is open: enter program loop (see SDL_PollEvent)
   done = 0;
  //Event loop
  while(!done)
  {
    //time
    gameState.time++;
    //Check for events
    if(gameState.acceptInput == 1){
        done = processEvents(window, &gameState);
    }
    //Render display
    doRender(renderer, &gameState);
    //don't burn up the CPU
    SDL_Delay(10);
  }

  shutDownGame(&gameState, window, renderer);

  return 0;
}

