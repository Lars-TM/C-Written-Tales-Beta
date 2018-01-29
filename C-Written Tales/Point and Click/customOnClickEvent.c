#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structDefinitions.h"
#include "data.h"


int checkIfNearEnough(GameState *game, int xPosition, int yPosition){

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

    if(xPosition > charXPos - NEARAREAEXTENTIONX && xPosition < charXPos + charWidth + NEARAREAEXTENTIONX){
            if(yPosition > charYPos - NEARAREAEXTENTIONY && yPosition < charYPos + charHeight + NEARAREAEXTENTIONY){
                            return 1;
            }
    }
    return 0;
}




int customOnClickEvent(GameState *game, int xPos, int yPos, int clickType){
    int idEventMaus;
    if(xPos > 0 && xPos < game->WINDOW_WIDTH && yPos > 0 && yPos < game->WINDOW_HEIGHT){
            idEventMaus = currentlyOnDisplay[xPos][yPos];
            if(xPos > 0 && xPos < game->WINDOW_WIDTH && yPos > 0 && yPos < game->GAME_WINDOW_BOTTOM){
                if(clickType == 0){
                    if(idEventMaus < 300){
                        printf("The ID is under 300. Id of Rendered Object %d\n",idEventMaus);
                        return 0;
                    }
                    if(idEventMaus < 550 && idEventMaus >= 300){
                        printf("The id %d is an interactive rendered Object\n",idEventMaus);
                        idEventMaus = idEventMaus - 300;
                        if(game->interactiveRenderedObjects[idEventMaus].clickable){
                            int EventId = game->interactiveRenderedObjects[idEventMaus].EventId;
                            int clickCount = game->interactiveRenderedObjects[idEventMaus].clickCount;
                            if(game->interactiveRenderedObjects[idEventMaus].OnlyUsableWhenNear == 0 || checkIfNearEnough(game, xPos, yPos) == 1){
                                startEvent(game, EventId, clickCount, idEventMaus+300);
                                printf("The id is clickable and has this Eventid %d and this clickCount %d\n", EventId, clickCount);
                                return 1;
                            }
                            else{
                                startEvent(game, 55, 0, 0);
                                printf("Not near enough!\n");
                            }
                        }
                    }

                    if(idEventMaus <= 1000 && idEventMaus >= 550){
                        printf("The id %d is an collectible\n",idEventMaus);
                        idEventMaus = idEventMaus - 550;
                        if(game->collectibleObjects[idEventMaus].clickable){
                            int EventId = game->collectibleObjects[idEventMaus].EventId;
                            int clickCount = game->collectibleObjects[idEventMaus].clickCount;
                            if(game->collectibleObjects[idEventMaus].OnlyUsableWhenNear == 0 || checkIfNearEnough(game, xPos, yPos) == 1){
                                startEvent(game, EventId, clickCount, idEventMaus+550);
                                printf("The id is clickable and has this Eventid %d and this clickCount %d\n", EventId, clickCount);
                                return 1;
                            }
                            else{
                                startEvent(game, 55, 0, 0);
                                printf("Not near enough!\n");
                            }
                        }
                    }
                }
                else if(clickType == 1){
                        if(game->idOfObjectMountedOnMouse != 0){
                            if(idEventMaus < 300 || (idEventMaus < 1000 && idEventMaus >= 550)){
                                game->idOfObjectMountedOnMouse = 0;
                                printf("You cant use Collectibles on RenderedObjects and Collectibles\n");
                                return 0;
                            }
                            if(idEventMaus >= 300 && idEventMaus < 550){
                                idEventMaus = idEventMaus - 300;
                                if(game->interactiveRenderedObjects[idEventMaus].interactiveWithObject){
                                    if(game->interactiveRenderedObjects[idEventMaus].idOfNeededObjectToInteract == game->idOfObjectMountedOnMouse){
                                        int EventId = game->interactiveRenderedObjects[idEventMaus].InteractionEventID;
                                        int clickCount = game ->interactiveRenderedObjects[idEventMaus].InteractionEventCount;
                                        printf("This interactive rendered Object with the id %d, clickCount %d and EventID %d is interactive with the mounted Collectible\n", idEventMaus, clickCount, EventId);
                                        if(game->interactiveRenderedObjects[idEventMaus].OnlyUsableWhenNear == 0 || checkIfNearEnough(game, xPos, yPos) == 1){
                                            startEvent(game, EventId, clickCount, idEventMaus+300);
                                            return 1;
                                        }
                                        else{
                                            startEvent(game, 55, 0, 0);
                                            printf("Not near enough!\n");
                                        }
                                    }
                                    return 0;
                                }
                            }
                        }
                }





            }
            if(xPos > 0 && xPos < game->WINDOW_WIDTH && yPos > 0 && yPos > game->GAME_WINDOW_BOTTOM){
                if(clickType == 0){
                    if(idEventMaus <= 1000 && idEventMaus >= 550){
                        printf("In Inventory - Collectible %d\n",idEventMaus);
                        idEventMaus = idEventMaus - 550;
                        if(game->collectibleObjects[idEventMaus].clickable){
                            int EventId = game->collectibleObjects[idEventMaus].EventId;
                            int clickCount = game->collectibleObjects[idEventMaus].clickCount;
                            startEvent(game, EventId, clickCount, idEventMaus+550);
                            printf("This collectible with the id %d, clickcount %d and EventID %d is interactive\n", idEventMaus, clickCount, EventId);
                            return 1;
                        }
                    }
                    else{

                        return 0;
                    }

                }
                if(clickType == 1){
                    if(game->idOfObjectMountedOnMouse > 0){
                        if(idEventMaus == game->idOfObjectMountedOnMouse){
                            game->idOfObjectMountedOnMouse = 0;
                            printf("You've just unmounted this collectible\n");
                            return 0;
                        }
                        if(idEventMaus >= 550 && idEventMaus < 1000){
                            printf("The id %d is an collectible\n", idEventMaus);
                            idEventMaus = idEventMaus - 550;
                            if(game->collectibleObjects[idEventMaus].ableToCraft){
                                if(game->collectibleObjects[idEventMaus].idOfNeededObjectToCraft == game->idOfObjectMountedOnMouse){
                                    int EventId = game->collectibleObjects[idEventMaus].CraftEventID;
                                    int clickCount = game ->collectibleObjects[idEventMaus].CraftEventCount;
                                    printf("It seems like the %d with the clickcount %d and the EventId %d wants to merge\n", idEventMaus, clickCount, EventId);
                                    startEvent(game, EventId, clickCount, idEventMaus+550);
                                    return 1;
                                    }
                                else{
                                    startEvent(game, 56, 0, 0);
                                    printf("It seems like this two hate each other\n");
                                    return 0;
                                }
                            }
                        }
                    }
                    else if(game->idOfObjectMountedOnMouse == 0){
                        idEventMaus = idEventMaus;
                        game->idOfObjectMountedOnMouse = idEventMaus;
                        printf("You've just mounted %d\n",idEventMaus);
                    }
                }
            }
            }
            return 0;
    }

