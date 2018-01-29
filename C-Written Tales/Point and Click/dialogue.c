#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structDefinitions.h"
#include "data.h"
#include "letEmSpeak.h"

int startRiddle(GameState *game, int RiddleID){
    addTextToShow(game, riddles[RiddleID][0]);
    game->acceptOnlyNumberInput = 1;

    int searchForAwnser = 1;
    while(searchForAwnser == 1){
        if(game->DialogueAnswer != 0){
            searchForAwnser = 0;
        }
    }
//    atoi ( const char * str )
    int rightAwnser = atoi(riddles[RiddleID][1]);
    int AnswerGiven = game->DialogueAnswer;
    game->DialogueAnswer = 0;

    deleteTextToShow(game);
    game->acceptOnlyNumberInput = 0;

    if(rightAwnser == AnswerGiven){
        game->DialogueAnswer = 0;
        printf("\nAnswer was right\n");
        return 42;
    } else{
        printf("\nAnswer was wrong\n");
        printf("Answer that was given: %d\n", AnswerGiven);
        return AnswerGiven;
    }
}

int startGetAnswerToQuestion(GameState *game, int TextID){
    addTextToShow(game, questions[TextID]);
    game->acceptOnlyNumberInput = 1;

    int searchForAwnser = 1;
    while(searchForAwnser == 1){
        if(game->DialogueAnswer != 0){
            searchForAwnser = 0;
        }
    }

    int AwnserGiven = game->DialogueAnswer;
    game->DialogueAnswer = 0;

    deleteTextToShow(game);
    game->acceptOnlyNumberInput = 0;

    printf("\nAnswer that was given: %d\n",AwnserGiven);
    return AwnserGiven;
}
