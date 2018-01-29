#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structDefinitions.h"
#include "data.h"
#include "dataOperations.h"
#include "letEmSpeak.h"

//Render Logic
void updateCurrentlyOnDisplay(GameState *game, int xPosition, int yPosition, int width, int height, int idToUpdate){
    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        xPosition = (int)((double)xPosition*multiplier);
        yPosition = (int)((double)yPosition*multiplier);
        width = (int)((double)width*multiplier);
        height = (int)((double)height*multiplier);
    }

    for(int j = xPosition; j < xPosition+width && j < game->WINDOW_WIDTH; j++){
    for(int i = yPosition; i < yPosition+height && i < game->WINDOW_HEIGHT; i++){
        currentlyOnDisplay[j][i] = idToUpdate;
    }
}
}

void updateAllowedToWalkHere(GameState *game, int xPosition, int yPosition, int width, int height, int idToUpdate){
    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        xPosition = (int)((double)xPosition*multiplier);
        yPosition = (int)((double)yPosition*multiplier);
        width = (int)((double)width*multiplier);
        height = (int)((double)height*multiplier);
    }

    for(int j = xPosition; j < xPosition+width && j < game->WINDOW_WIDTH; j++){
    for(int i = yPosition; i < yPosition+height && i < game->WINDOW_HEIGHT; i++){
        AllowedToWalkHere[j][i] = idToUpdate;
    }
}
}

void drawImage(GameState *game, SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int width, int height){
    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        x = (int)((double)x*multiplier);
        y = (int)((double)y*multiplier);
        width = (int)((double)width*multiplier);
        height = (int)((double)height*multiplier);
    }

        SDL_Rect imageRect = { x, y, width, height };
        SDL_RenderCopy(renderer, texture, NULL, &imageRect);
}

void drawRectangle(GameState *game, SDL_Renderer *renderer, int x, int y, int width, int height){
    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        x = (int)((double)x*multiplier);
        y = (int)((double)y*multiplier);
        width = (int)((double)width*multiplier);
        height = (int)((double)height*multiplier);
    }
          //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

        SDL_Rect Rect = { x, y, width, height };
        SDL_RenderFillRect(renderer, &Rect);
        SDL_RenderCopy(renderer, NULL, NULL, &Rect);
}

void drawLayer(GameState *game, int LayerToDraw, int roomToDraw){

    int CountOfArray;
    int *UsedArray;

    if(LayerToDraw == 0){
        CountOfArray = game->countObjectsIn_Ways[roomToDraw];
        UsedArray = game->Ways[roomToDraw];
    }

    if(LayerToDraw == 1){
        CountOfArray = game->countObjectsIn_Background[roomToDraw];
        UsedArray = game->Background[roomToDraw];
    }

    if(LayerToDraw == 2){
        CountOfArray = game->countObjectsIn_LayerTwo[roomToDraw];
        UsedArray = game->LayerTwo[roomToDraw];
    }

    if(LayerToDraw == 3){
        CountOfArray = game->countObjectsIn_LayerThree[roomToDraw];
        UsedArray = game->LayerThree[roomToDraw];
    }

    if(LayerToDraw == 4){
        CountOfArray = game->countObjectsIn_LayerFour[roomToDraw];
        UsedArray = game->LayerFour[roomToDraw];
    }

    if(LayerToDraw == 5){
        CountOfArray = game->countObjectsIn_LayerFive[roomToDraw];
        UsedArray = game->LayerFive[roomToDraw];
    }

    if(LayerToDraw == 6){
        CountOfArray = game->countObjectsIn_Foreground[roomToDraw];
        UsedArray = game->Foreground[roomToDraw];
    }

    if(LayerToDraw == 7){
        CountOfArray = game->countObjectsIn_Blackscreen[roomToDraw];
        UsedArray = game->Blackscreen[roomToDraw];
    }


if(CountOfArray > 0){
    int stillObjectsToDraw = 1;
    int i = 0;
    while(stillObjectsToDraw == 1){
        int idOfObjectToDraw = UsedArray[i];

        if(idOfObjectToDraw<300){
            int idToUse = idOfObjectToDraw;
            drawImage(game, game->renderer, game->textures[game->renderedObjects[idToUse].imgID],
                      game->renderedObjects[idToUse].xPosition, game->renderedObjects[idToUse].yPosition,
                      game->renderedObjects[idToUse].width, game->renderedObjects[idToUse].height);
            if(LayerToDraw > 0 && LayerToDraw < 6){
                    if(LayerToDraw < 5){
                        updateAllowedToWalkHere(game ,game->renderedObjects[idToUse].xPosition, game->renderedObjects[idToUse].yPosition,
                                             game->renderedObjects[idToUse].width, game->renderedObjects[idToUse].height, idOfObjectToDraw);
                    }
                    updateCurrentlyOnDisplay(game ,game->renderedObjects[idToUse].xPosition, game->renderedObjects[idToUse].yPosition,
                                             game->renderedObjects[idToUse].width, game->renderedObjects[idToUse].height, idOfObjectToDraw);
            }


        }

        if(idOfObjectToDraw >= 300 && idOfObjectToDraw < 550){
            int idToUse = idOfObjectToDraw-300;
            drawImage(game, game->renderer, game->textures[game->interactiveRenderedObjects[idToUse].imgID],
                      game->interactiveRenderedObjects[idToUse].xPosition, game->interactiveRenderedObjects[idToUse].yPosition,
                      game->interactiveRenderedObjects[idToUse].width, game->interactiveRenderedObjects[idToUse].height);
            if(LayerToDraw > 0 && LayerToDraw < 6){
                    if(LayerToDraw < 5){
                        updateAllowedToWalkHere(game ,game->interactiveRenderedObjects[idToUse].xPosition, game->interactiveRenderedObjects[idToUse].yPosition,
                                             game->interactiveRenderedObjects[idToUse].width, game->interactiveRenderedObjects[idToUse].height, idOfObjectToDraw);
                    }
                    updateCurrentlyOnDisplay(game ,game->interactiveRenderedObjects[idToUse].xPosition, game->interactiveRenderedObjects[idToUse].yPosition,
                                             game->interactiveRenderedObjects[idToUse].width, game->interactiveRenderedObjects[idToUse].height, idOfObjectToDraw);
            }
        }

        if(idOfObjectToDraw >= 550){
            int idToUse = idOfObjectToDraw-550;
            drawImage(game, game->renderer, game->textures[game->collectibleObjects[idToUse].imgID],
                      game->collectibleObjects[idToUse].xPosition, game->collectibleObjects[idToUse].yPosition,
                      game->collectibleObjects[idToUse].width, game->collectibleObjects[idToUse].height);
            if(LayerToDraw > 0){
                    if(LayerToDraw < 5){
                        updateAllowedToWalkHere(game ,game->collectibleObjects[idToUse].xPosition, game->collectibleObjects[idToUse].yPosition,
                                             game->collectibleObjects[idToUse].width, game->collectibleObjects[idToUse].height, idOfObjectToDraw);
                    }
                    updateCurrentlyOnDisplay(game ,game->collectibleObjects[idToUse].xPosition, game->collectibleObjects[idToUse].yPosition,
                                             game->collectibleObjects[idToUse].width, game->collectibleObjects[idToUse].height, idOfObjectToDraw);
            }
        }

        i++;
        if(i >= CountOfArray){
            stillObjectsToDraw = 0;
        }
    }
}


}

void drawInventory(GameState *game){

    int imgIDOfInventoryBackground = 62;
    int imgIDOfMountedOnMouseIcon = 63;

    updateCurrentlyOnDisplay(game, 0,675,1200,125,0);

    drawImage(game, game->renderer, game->textures[imgIDOfInventoryBackground], 0, 675, 1200, 125);


if(game->countObjectsInInventory > 0){
    int stillObjectsToDraw = 1;
    int i = game->PositionInInventory;
    int positionOfOjectInInventory = 150;
    int counterToNine = 0;
    while(stillObjectsToDraw == 1){
        int idOfObjectToDraw = game->objectsInInventory[i];
        int idToUse = idOfObjectToDraw - 550;
        drawImage(game, game->renderer, game->textures[game->collectibleObjects[idToUse].imgID], positionOfOjectInInventory, 685, 100, 100);
        if(game->idOfObjectMountedOnMouse == idOfObjectToDraw){
            drawImage(game, game->renderer, game->textures[imgIDOfMountedOnMouseIcon], positionOfOjectInInventory+80, 765, 20, 20);
        }
        updateCurrentlyOnDisplay(game ,positionOfOjectInInventory, 685, 100, 100, idOfObjectToDraw);
        positionOfOjectInInventory += 110;
        i++;
        counterToNine++;
        if( i >= game->countObjectsInInventory || counterToNine > 8){
            stillObjectsToDraw = 0;
        }
    }
}
}

void animateCharackter(GameState *game, int direction){
    if(game->time%ANIMATION_SPEED_CHARACKTER == 0){
    if(direction == 0){
        if(game->person.imgID == 0){
            game->person.imgID = 1;
        } else{
            game->person.imgID = 0;
        }
    }

    if(direction == 1){
        if(game->person.imgID == 2){
            game->person.imgID = 3;
        } else{
            game->person.imgID = 2;
        }
    }

    if(direction == 2){
        if(game->person.imgID == 4){
            game->person.imgID = 5;
        } else{
            game->person.imgID = 4;
        }
    }

    if(direction == 3){
        if(game->person.imgID == 6){
            game->person.imgID = 7;
        } else{
            game->person.imgID = 6;
        }
    }
    }
}

void loopAnimateObjects(GameState *game){
    if(game->time%ANIMATION_SPEED == 0){

    for(int i = 0; i < game->countObjectsIn_LoopAnimations; i++){

                if(animationArray[game->LoopAnimations[i][1]][0] < animationArray[game->LoopAnimations[i][1]][1]-1){
                    animationArray[game->LoopAnimations[i][1]][0]++;

                } else{
                    animationArray[game->LoopAnimations[i][1]][0] = 0;

                }


                if(game->LoopAnimations[i][0] < 300){
                   game->renderedObjects[game->LoopAnimations[i][0]].imgID =
                            animationArray[game->LoopAnimations[i][1]][animationArray[game->LoopAnimations[i][1]][0]+2];
                }

                if(game->LoopAnimations[i][0] >= 300 && game->LoopAnimations[i][0] < 550){
                   game->interactiveRenderedObjects[game->LoopAnimations[i][0]-300].imgID =
                            animationArray[game->LoopAnimations[i][1]][animationArray[game->LoopAnimations[i][1]][0]+2];
                }

                if(game->LoopAnimations[i][0] >= 550){
                   game->collectibleObjects[game->LoopAnimations[i][0]-550].imgID =
                            animationArray[game->LoopAnimations[i][1]][animationArray[game->LoopAnimations[i][1]][0]+2];
                }

    }
    }
}

void OneTimeAnimateObjects(GameState *game){
if(game->time%ANIMATION_SPEED == 0){
        int endAnimation = 0;

    for(int i = 0; i < game->countObjectsIn_OneTimeAnimations; i++){

                if(animationArray[game->OneTimeAnimations[i][1]][0] < animationArray[game->OneTimeAnimations[i][1]][1]-1){
                    animationArray[game->OneTimeAnimations[i][1]][0]++;

                } else{
                    endAnimation = 1;
                    animationArray[game->OneTimeAnimations[i][1]][0] = 0;
                }


                if(game->OneTimeAnimations[i][0] < 300){
                   game->renderedObjects[game->OneTimeAnimations[i][0]].imgID =
                            animationArray[game->OneTimeAnimations[i][1]][animationArray[game->OneTimeAnimations[i][1]][0]+2];
                }

                if(game->OneTimeAnimations[i][0] >= 300 && game->OneTimeAnimations[i][0] < 550){
                   game->interactiveRenderedObjects[game->OneTimeAnimations[i][0]-300].imgID =
                            animationArray[game->OneTimeAnimations[i][1]][animationArray[game->OneTimeAnimations[i][1]][0]+2];
                }

                if(game->OneTimeAnimations[i][0] >= 550){
                   game->collectibleObjects[game->OneTimeAnimations[i][0]-550].imgID =
                            animationArray[game->OneTimeAnimations[i][1]][animationArray[game->OneTimeAnimations[i][1]][0]+2];
                }
      if (endAnimation == 1){
        removeObjectFrom_OneTimeAnimations(game, game->OneTimeAnimations[i][0]);;
      }

    }


}
}


void doRender(SDL_Renderer *renderer, GameState *game)
{
  OneTimeAnimateObjects(game);
  loopAnimateObjects(game);
  //set the drawing color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  //Clear the screen (to black)
  SDL_RenderClear(renderer);

  //draw the image

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



 //printf("First %d\n", game->currentRoom);
    drawLayer(game,0,game->currentRoom);//Is neither in currently on Display nor affects restrictions to walk

   // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    //drawRectangle(game,renderer,game->person.x - NEARAREAEXTENTIONX, game->person.y - NEARAREAEXTENTIONY, game->PERSON_WIDTH + 2*NEARAREAEXTENTIONX, game->PERSON_HEIGHT + 2*NEARAREAEXTENTIONY);

    drawLayer(game,1,game->currentRoom);//Is in currently on Display and affects restrictions to walk
    drawLayer(game,2,game->currentRoom);//Is in currently on Display and affects restrictions to walk
    drawLayer(game,3,game->currentRoom);//Is in currently on Display and affects restrictions to walk
    drawLayer(game,4,game->currentRoom);//Is in currently on Display and affects restrictions to walk


    if(game->actualGame == 1){
    drawImage(game, renderer, game->textures[game->person.imgID], game->person.x, game->person.y, game->PERSON_WIDTH, game->PERSON_HEIGHT);
    }
    drawLayer(game,5,game->currentRoom); //Is in currently on Display, but does not affect restrictions to walk
    drawLayer(game, 6, game->currentRoom);  //Is neither in currently on Display nor affects restrictions to walk
    drawLayer(game, 7, game->currentRoom);
    if(game->actualGame == 1){
    drawInventory(game);
    drawTextLayer(game);
    }
  //  printf("%d\n", game->currentRoom);

  //set the drawing color to white
  //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);



  //draw a rectangle at man's position
  //drawImage(game, renderer, game->textures[game->person.imgID], game->person.x, game->person.y, game->personWidth, game->personHeight);



//  SDL_RenderFillRect(renderer, &rect);



  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}
