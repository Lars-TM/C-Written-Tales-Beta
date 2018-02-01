#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structDefinitions.h"
#include "data.h"
#include "audio.h"


void addTextToShow(GameState *game, char text[200]){
    strcpy(game->TextToShow, text);
}

void deleteTextToShow(GameState *game){
    strcpy(game->TextToShow, "");
}

void showText(GameState *game, char text[200]){
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderText_Blended(game->fontToUse,
    text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    if(game->WINDOW_WIDTH != 1200){
        double multiplier = (double)game->WINDOW_WIDTH/(double)1200;
        texW = (int)((double)texW*multiplier);
        texH = (int)((double)texH*multiplier);
    }

    int xPositionOfText = (int)((double)game->WINDOW_WIDTH/(double)2) - texW/2;
    int yPositionOfText = game->GAME_WINDOW_BOTTOM - texH*2;



    SDL_Rect dstrect = { xPositionOfText, yPositionOfText, texW, texH };
    SDL_RenderCopy(game->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void letEmSpeak(GameState *game, int letEmSpeakId){
    game->acceptOnlyNumberInput = 1;
    game->acceptInput = 0;
    playSound(game, letEmSpeakArray[letEmSpeakId][0], 0);
    addTextToShow(game, texts[letEmSpeakArray[letEmSpeakId][1]]);
    sleep_ms(letEmSpeakArray[letEmSpeakId][2]);
    deleteTextToShow(game);
    game->acceptInput = 1;
    game->acceptOnlyNumberInput = 0;
}

void drawTextLayer(GameState *game){
    showText(game, game->TextToShow);
}
