#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "structDefinitions.h"
#include "data.h"



//Game Logic - Render - Load
int loadImagesInMemory(GameState *game){
    for(int i = 0; i < NUMBER_OF_IMAGES_TO_LOAD; i++){
        SDL_Surface *imgLoadSurface = NULL;

        //Load images and create rendering textures from them
        imgLoadSurface = IMG_Load(imgSource[i]);
        if(imgLoadSurface == NULL)
        {
        printf( "  \263         \263   \263__Cannot find [%s]\n", imgSource[i]);
        return 0;
        //SDL_Quit();
        //exit(1);
        }

        game->textures[i] = SDL_CreateTextureFromSurface(game->renderer, imgLoadSurface);
        SDL_FreeSurface(imgLoadSurface);
        printf( "  \263      \263   \263  Loaded [%s]\n", imgSource[i]);
    }
    return 1;
}

//Game Logic - Audio - Load
int loadAudioInMemory(GameState *game){
    printf("  \263         \263\n  \263         \263__Load Background music...\n");
    for(int i = 0; i < NUMBER_OF_BACKGROUNDMUSICS_TO_LOAD; i++){

        game->gMusic[i] = NULL;
        game->gMusic[i] = Mix_LoadMUS(musicSource[i]);
    if( game->gMusic[i] == NULL )
    {
        printf( "  \263         \263   \263__Failed to load[%s]! SDL_mixer Error: %s\n",musicSource[i], Mix_GetError() );
        return 0;
    }
        printf( "  \263         \263   \263  Loaded [%s]\n", musicSource[i]);
    }
    printf("  \263         \263   \263__Background music loaded successfully\n  \263         \263  \n");

    printf("  \263         \263__Load Sounds...\n");
    for(int i = 0; i < NUMBER_OF_SOUNDS_TO_LOAD; i++){

        game->gSounds[i] = NULL;
        //Load sound effects
        game->gSounds[i] = Mix_LoadWAV(soundSource[i]);
    if( game->gSounds[i] == NULL )
    {
        printf( "  \263         \263   \263__Failed to load[%s]! SDL_mixer Error: %s\n",soundSource[i], Mix_GetError() );
        return 0;
    }
        printf( "  \263         \263   \263  Loaded [%s]\n", soundSource[i]);
    }
    printf("  \263         \263   \263__Sounds loaded successfully\n  \263         \263  \n");
    return 1;
}

//Data Logic - initialArrays
void fillRenderedObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID){
        game->renderedObjects[index].id = id;
        game->renderedObjects[index].xPosition = xPosition;
        game->renderedObjects[index].yPosition = yPosition;
        game->renderedObjects[index].width = width;
        game->renderedObjects[index].height = height;
        game->renderedObjects[index].imgID = imgID;

}

void fillInteractiveRenderedObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID,
                                     bool clickable, int clickCount, int EventID, bool interactiveWithObject, int idOfNeededObjectToInteract,
                                     bool OnlyUsableWhenNear, int InteractionEventID, int InteractionEventCount){
        game->interactiveRenderedObjects[index].id = id;
        game->interactiveRenderedObjects[index].xPosition = xPosition;
        game->interactiveRenderedObjects[index].yPosition = yPosition;
        game->interactiveRenderedObjects[index].width = width;
        game->interactiveRenderedObjects[index].height = height;
        game->interactiveRenderedObjects[index].imgID = imgID;

        game->interactiveRenderedObjects[index].clickable = clickable;
        game->interactiveRenderedObjects[index].clickCount = clickCount;
        game->interactiveRenderedObjects[index].EventId = EventID;

        game->interactiveRenderedObjects[index].interactiveWithObject = interactiveWithObject;
        game->interactiveRenderedObjects[index].idOfNeededObjectToInteract = idOfNeededObjectToInteract;

        game->interactiveRenderedObjects[index].OnlyUsableWhenNear = OnlyUsableWhenNear;

        game->interactiveRenderedObjects[index].InteractionEventID = InteractionEventID;
        game->interactiveRenderedObjects[index].InteractionEventCount = InteractionEventCount;

}

void fillCollectibleObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID,
                            bool clickable, int clickCount, int EventID, bool ableToCraft, int idOfNeededObjectToCraft,
                            bool OnlyUsableWhenNear, int CraftEventID, int CraftEventCount){
        game->collectibleObjects[index].id = id;
        game->collectibleObjects[index].xPosition = xPosition;
        game->collectibleObjects[index].yPosition = yPosition;
        game->collectibleObjects[index].width = width;
        game->collectibleObjects[index].height = height;
        game->collectibleObjects[index].imgID = imgID;

        game->collectibleObjects[index].clickable = clickable;
        game->collectibleObjects[index].clickCount = clickCount;
        game->collectibleObjects[index].EventId = EventID;

        game->collectibleObjects[index].ableToCraft = ableToCraft;
        game->collectibleObjects[index].idOfNeededObjectToCraft = idOfNeededObjectToCraft;

        game->collectibleObjects[index].OnlyUsableWhenNear = OnlyUsableWhenNear;

        game->collectibleObjects[index].CraftEventID = CraftEventID;
        game->collectibleObjects[index].CraftEventCount = CraftEventCount;
}


//Data Logic - runtimeArrays
void initRuntimeArrays(GameState *game){
    game->countObjectsInInventory = 0;
    for(int i = 0; i < 10; i++){
        game->countObjectsIn_Ways[i] = 0;
        game->countObjectsIn_Background[i] = 0;
        game->countObjectsIn_LayerTwo[i] = 0;
        game->countObjectsIn_LayerThree[i] = 0;
        game->countObjectsIn_LayerFour[i] = 0;
        game->countObjectsIn_LayerFive[i] = 0;
        game->countObjectsIn_Foreground[i] = 0;
        game->countObjectsIn_Blackscreen[i] = 0;
    }
    game->PositionInInventory = 0;
    game->countObjectsIn_LoopAnimations = 0;
    game->countObjectsIn_OneTimeAnimations = 0;
    strcpy(game->TextToShow, "");
    game->currentRoom = 9;
    game->acceptOnlyNumberInput = 0;
    game->DialogueAnswer = 0;
    game->idOfObjectMountedOnMouse = 0;
    game->actualGame = 0;
    game->acceptNoArrowInput = 0;
}

void addObjectTo_ObjectsInInventory(GameState *game, int idToAdd){
    //printf("idToAdd: %d . 1\n", idToAdd);
    game->objectsInInventory[game->countObjectsInInventory] = idToAdd;
    //printf("idToAdd: %d . 2\n", idToAdd);
    game->countObjectsInInventory++;
}

void removeObjectFrom_ObjectsInInventory(GameState *game, int idToDelete){
    int i = 0;

    while(i < game->countObjectsInInventory && game->objectsInInventory[i] != idToDelete){
        i++;
    }

    if(i < game->countObjectsInInventory){

        for(int j = i; j < game->countObjectsInInventory; ++j){
            game->objectsInInventory[j] = game->objectsInInventory[j+1];
            game->objectsInInventory[j+1] = 0;
        }
        game->countObjectsInInventory--;
    }



}


void addObjectTo_Array(GameState *game,int roomToAddTo, int ArrayToAdd, int idToAdd){

    if(ArrayToAdd == 0){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->Ways[roomToAddTo][game->countObjectsIn_Ways[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_Ways[roomToAddTo]++;
    }

    if(ArrayToAdd == 1){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->Background[roomToAddTo][game->countObjectsIn_Background[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_Background[roomToAddTo]++;
    }

    if(ArrayToAdd == 2){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->LayerTwo[roomToAddTo][game->countObjectsIn_LayerTwo[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_LayerTwo[roomToAddTo]++;
    }

    if(ArrayToAdd == 3){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->LayerThree[roomToAddTo][game->countObjectsIn_LayerThree[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_LayerThree[roomToAddTo]++;
    }

    if(ArrayToAdd == 4){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->LayerFour[roomToAddTo][game->countObjectsIn_LayerFour[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_LayerFour[roomToAddTo]++;
    }

    if(ArrayToAdd == 5){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->LayerFive[roomToAddTo][game->countObjectsIn_LayerFive[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_LayerFive[roomToAddTo]++;
    }

    if(ArrayToAdd == 6){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->Foreground[roomToAddTo][game->countObjectsIn_Foreground[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_Foreground[roomToAddTo]++;
    }

    if(ArrayToAdd == 7){
        //printf("Array to add: %d  idToAdd: %d . 1\n",ArrayToAdd, idToAdd);
        game->Blackscreen[roomToAddTo][game->countObjectsIn_Blackscreen[roomToAddTo]] = idToAdd;
        //printf("idToAdd: %d . 2\n", idToAdd);
        game->countObjectsIn_Blackscreen[roomToAddTo]++;
    }



}

void removeObjectFrom_Array(GameState *game,int roomToDeleteFrom, int ArrayToChange, int idToDelete){

    if(ArrayToChange == 0){
        int i = 0;
        while(i < game->countObjectsIn_Ways[roomToDeleteFrom] && game->Ways[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_Ways[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_Ways[roomToDeleteFrom]; ++j){
            game->Ways[roomToDeleteFrom][j] = game->Ways[roomToDeleteFrom][j+1];
            game->Ways[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_Ways[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 1){
        int i = 0;
        while(i < game->countObjectsIn_Background[roomToDeleteFrom] && game->Background[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_Background[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_Background[roomToDeleteFrom]; ++j){
            game->Background[roomToDeleteFrom][j] = game->Background[roomToDeleteFrom][j+1];
            game->Background[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_Background[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 2){
        int i = 0;
        while(i < game->countObjectsIn_LayerTwo[roomToDeleteFrom] && game->LayerTwo[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_LayerTwo[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_LayerTwo[roomToDeleteFrom]; ++j){
            game->LayerTwo[roomToDeleteFrom][j] = game->LayerTwo[roomToDeleteFrom][j+1];
            game->LayerTwo[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_LayerTwo[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 3){
        int i = 0;
        while(i < game->countObjectsIn_LayerThree[roomToDeleteFrom] && game->LayerThree[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_LayerThree[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_LayerThree[roomToDeleteFrom]; ++j){
            game->LayerThree[roomToDeleteFrom][j] = game->LayerThree[roomToDeleteFrom][j+1];
            game->LayerThree[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_LayerThree[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 4){
        int i = 0;
        while(i < game->countObjectsIn_LayerFour[roomToDeleteFrom] && game->LayerFour[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_LayerFour[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_LayerFour[roomToDeleteFrom]; ++j){
            game->LayerFour[roomToDeleteFrom][j] = game->LayerFour[roomToDeleteFrom][j+1];
            game->LayerFour[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_LayerFour[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 5){
        int i = 0;
        while(i < game->countObjectsIn_LayerFive[roomToDeleteFrom] && game->LayerFive[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_LayerFive[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_LayerFive[roomToDeleteFrom]; ++j){
            game->LayerFive[roomToDeleteFrom][j] = game->LayerFive[roomToDeleteFrom][j+1];
            game->LayerFive[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_LayerFive[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 6){
        int i = 0;
        while(i < game->countObjectsIn_Foreground[roomToDeleteFrom] && game->Foreground[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_Foreground[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_Foreground[roomToDeleteFrom]; ++j){
            game->Foreground[roomToDeleteFrom][j] = game->Foreground[roomToDeleteFrom][j+1];
            game->Foreground[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_Foreground[roomToDeleteFrom]--;
    }
    }

    if(ArrayToChange == 7){
        int i = 0;
        while(i < game->countObjectsIn_Blackscreen[roomToDeleteFrom] && game->Blackscreen[roomToDeleteFrom][i] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_Blackscreen[roomToDeleteFrom]){

        for(int j = i; j < game->countObjectsIn_Blackscreen[roomToDeleteFrom]; ++j){
            game->Blackscreen[roomToDeleteFrom][j] = game->Blackscreen[roomToDeleteFrom][j+1];
            game->Blackscreen[roomToDeleteFrom][j+1] = 0;
        }
        game->countObjectsIn_Blackscreen[roomToDeleteFrom]--;
    }
    }



}

void addObjectTo_OneTimeAnimations(GameState *game, int idToAdd_Object, int AnimationId){
        game->OneTimeAnimations[game->countObjectsIn_OneTimeAnimations][0] = idToAdd_Object;
        game->OneTimeAnimations[game->countObjectsIn_OneTimeAnimations][1] = AnimationId;
        game->countObjectsIn_OneTimeAnimations++;
}

void setLoopAnitmationToFirstPicture(GameState *game, int placeOfObjectInArray){

                animationArray[game->LoopAnimations[placeOfObjectInArray][1]][0] = 0;

                if(game->LoopAnimations[placeOfObjectInArray][0] < 300){
                   game->renderedObjects[game->LoopAnimations[placeOfObjectInArray][0]].imgID =
                            animationArray[game->LoopAnimations[placeOfObjectInArray][1]][animationArray[game->LoopAnimations[placeOfObjectInArray][1]][0]];
                }
                if(game->LoopAnimations[placeOfObjectInArray][0] >= 300 && game->LoopAnimations[placeOfObjectInArray][0] < 550){
                   game->interactiveRenderedObjects[game->LoopAnimations[placeOfObjectInArray][0]-300].imgID =
                            animationArray[game->LoopAnimations[placeOfObjectInArray][1]][animationArray[game->LoopAnimations[placeOfObjectInArray][1]][0]];
                }
                if(game->LoopAnimations[placeOfObjectInArray][0] >= 550){
                   game->collectibleObjects[game->LoopAnimations[placeOfObjectInArray][0]-550].imgID =
                            animationArray[game->LoopAnimations[placeOfObjectInArray][1]][animationArray[game->LoopAnimations[placeOfObjectInArray][1]][0]];
                }

}

void removeObjectFrom_OneTimeAnimations(GameState *game, int idToDelete){
        int i = 0;
        while(i < game->countObjectsIn_OneTimeAnimations && game->OneTimeAnimations[i][0] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_OneTimeAnimations){

                setLoopAnitmationToFirstPicture(game, i);

        for(int j = i; j < game->countObjectsIn_LoopAnimations; ++j){
            game->OneTimeAnimations[j][0] = game->OneTimeAnimations[j+1][0];
            game->OneTimeAnimations[j][1] = game->OneTimeAnimations[j+1][1];
            game->OneTimeAnimations[j+1][0] = 0;
            game->OneTimeAnimations[j+1][1] = 0;

        }
        game->countObjectsIn_OneTimeAnimations--;
    }
}

void addObjectTo_LoopAnimations(GameState *game, int idToAdd_Object, int AnimationId){
        game->LoopAnimations[game->countObjectsIn_LoopAnimations][0] = idToAdd_Object;
        game->LoopAnimations[game->countObjectsIn_LoopAnimations][1] = AnimationId;
        game->countObjectsIn_LoopAnimations++;
}

void removeObjectFrom_LoopAnimations(GameState *game, int idToDelete){
        int i = 0;
        while(i < game->countObjectsIn_LoopAnimations && game->LoopAnimations[i][0] != idToDelete){
            i++;
        }

        if(i < game->countObjectsIn_LoopAnimations){

        for(int j = i; j < game->countObjectsIn_LoopAnimations; ++j){
            game->LoopAnimations[j][0] = game->LoopAnimations[j+1][0];
            game->LoopAnimations[j][1] = game->LoopAnimations[j+1][1];
            game->LoopAnimations[j+1][0] = 0;
            game->LoopAnimations[j+1][1] = 0;

        }
        game->countObjectsIn_LoopAnimations--;
    }
}

void removeFromGameDisplay(GameState *game, int roomToDeleteFrom, int idToRemove){
    removeObjectFrom_Array(game,roomToDeleteFrom, 0, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 1, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 2, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 3, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 4, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 5, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 6, idToRemove);
    removeObjectFrom_Array(game,roomToDeleteFrom, 7, idToRemove);
}

void clearGameDisplay(GameState *game, int roomToClear){

    for(int i = 0; i < game->countObjectsIn_Ways[roomToClear]; i++){
        game->Ways[roomToClear][i] = 0;
    }
    game->countObjectsIn_Ways[roomToClear] = 0;

    for(int i = 0; i < game->countObjectsIn_Background[roomToClear]; i++){
        game->Background[roomToClear][i] = 0;
    }
    game->countObjectsIn_Background[roomToClear] = 0;

    for(int i = 0; i < game->countObjectsIn_LayerTwo[roomToClear]; i++){
        game->LayerTwo[roomToClear][i] = 0;
    }
    game->countObjectsIn_LayerTwo[roomToClear] = 0;

    for(int i = 0; i < game->countObjectsIn_LayerThree[roomToClear]; i++){
        game->LayerThree[roomToClear][i] = 0;
    }
    game->countObjectsIn_LayerThree[roomToClear] = 0;

    for(int i = 0; i < game->countObjectsIn_LayerFour[roomToClear]; i++){
        game->LayerFour[roomToClear][i] = 0;
    }
    game->countObjectsIn_LayerFour[roomToClear] = 0;

    for(int i = 0; i < game->countObjectsIn_LayerFive[roomToClear]; i++){
        game->LayerFive[roomToClear][i] = 0;
    }
    game->countObjectsIn_LayerFive[roomToClear] = 0;

}
