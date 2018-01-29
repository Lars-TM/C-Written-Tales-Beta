#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structDefinitions.h"
#include "data.h"
#include "dataOperations.h"


void startMusic(GameState *game, int musicID){


    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
    //Play the music
    Mix_PlayMusic( game->gMusic[musicID], -1 );
    }
    //If music is being played
    else
    {
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
    //Resume the music
    Mix_HaltMusic();
    Mix_PlayMusic( game->gMusic[musicID], -1 );
    }
    //If the music is playing
    else
    {
    //Pause the music
    Mix_HaltMusic();
    Mix_PlayMusic( game->gMusic[musicID], -1 );
    }
    }

}

void stopMusic(GameState *game){


    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
    }
    //If music is being played
    else
    {
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
    //Resume the music
    Mix_HaltMusic();
    }
    //If the music is playing
    else
    {
    Mix_HaltMusic();
    }
    }

}

void playSound(GameState *game, int soundID, int looops){
    Mix_PlayChannel( -1, game->gSounds[soundID], looops );
}
