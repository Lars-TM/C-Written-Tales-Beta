#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structDefinitions.h"
#include "data.h"
#include "letEmSpeak.h"
#include "main.h"

int startRiddle(GameState *game, int RiddleID){
    addTextToShow(game, riddles[RiddleID][0]);
    game->acceptOnlyNumberInput = 1;

    int searchForAwnser = 1;
    while(searchForAwnser == 1){
        if(game->riddleAwnser != 0){
            searchForAwnser = 0;
        }
    }
//    atoi ( const char * str )
    int rightAwnser = atoi(riddles[RiddleID][1]);    //HIER
    int AwnserGiven = game->riddleAwnser;
    game->riddleAwnser = 0;

    deleteTextToShow(game);
    game->acceptOnlyNumberInput = 0;

    if(rightAwnser == AwnserGiven){
        game->riddleAwnser = 0;
                printf("Richtig");

        return 42;
    } else{
        printf("Falsch");
        return AwnserGiven;
    }
}

int startGetAwnserToQuestion(GameState *game, int TextID){
    addTextToShow(game, texts[TextID]);
    game->acceptOnlyNumberInput = 1;

    int searchForAwnser = 1;
    while(searchForAwnser == 1){
        if(game->riddleAwnser != 0){
            searchForAwnser = 0;
        }
    }

    int AwnserGiven = game->riddleAwnser;
    game->riddleAwnser = 0;

    deleteTextToShow(game);
    game->acceptOnlyNumberInput = 0;

    printf("%d",AwnserGiven);
    return AwnserGiven;
}
