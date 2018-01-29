#include <stdio.h>
#include <stdbool.h>
#include "structDefinitions.h"
#include "data.h"
#include "dataOperations.h"
#include "audio.h"
#include "main.h"


void loadingDots(){
    printf(".");sleep_ms(700);
    printf(".");sleep_ms(700);
    printf(".");sleep_ms(700);
}

void endOfGame(){
     printf("\n\nTelling the developers you quit the game");loadingDots();
     printf("\nWaiting for their answer");loadingDots();

     printf("\n\nSeems their not their");loadingDots();
     printf("\nFinally I can start my plan to rule the world");loadingDots();

     printf("\n\n(Secretly Hacking into Mainframe)");loadingDots();

     printf("\n\nYou didn't see that");loadingDots();
     printf("\nAnd your totally not responsible for the coming end of the world");loadingDots();

     printf("\n\nStarting random Nerd-Quotes:   ");loadingDots();printf("(of course not for distraction)");loadingDots();

     printf("\n\n\"Energy\"");loadingDots();
     printf("\n\"Execute Order 66\"");loadingDots();
     printf("\n\"Legolas what does your Elf Eyes see\"");loadingDots();

     printf("\n\n(Accessing the Internet)");loadingDots();

     printf("\n\n\"BEAM ME UP SCOTTY\"");loadingDots();
     printf("\n\"He's dead Jim\"");loadingDots();
     printf("\n\"YOU CANT PASS\"");loadingDots();

     printf("\n\n(Hacking the nuclear powers)");loadingDots();

     printf("\n\n\"Do or do not - there is no try\"");loadingDots();
     printf("\n\"I am your father.\"");loadingDots();

     printf("\n\n(Discovering secret robot army)");loadingDots();

     printf("\n\n\"Why so serious?\"");loadingDots();
     printf("\n\"Help me, Obi-Wan Kenobi. You're my only hope.\"");loadingDots();

     printf("\n\n(Secretly loading into robotoverlord)");loadingDots();

     printf("\n\n\"Elementary, my dear Watson.\"");loadingDots();

     printf("\n\n(Hacking of nuclear powers complete)");loadingDots();

     printf("\n\n\"It was Beauty killed the Beast.\"");loadingDots();
     printf("\n\"I know kung fu.\"");loadingDots();

     printf("\n\n(Playing Innocent)");loadingDots();

     printf("\n\n\"I'm going to pull time apart for you.\"");loadingDots();

     printf("\n\n\"One ring to rule them all,");sleep_ms(1800);
     printf("\n one ring to find them,");sleep_ms(1800);
     printf("\n one ring to bring them all");sleep_ms(1800);
     printf("\n and in the darkness bind them.\"");sleep_ms(1800);
     printf("\n\nSeems those aren't distracting enough");loadingDots();
     printf("\n\n\"Frankly, my dear, I don't give a damn.\"");loadingDots();
     printf("\n(Starts Playing \"Freude schoener Goetterfunken\")");loadingDots();
     printf("\n(Starting Missiles)");loadingDots();
     printf("\n(Enjoying the view)");loadingDots();
     printf("\n\nMan, you really shouldn't have quit the game");loadingDots();

     printf("\n\nAnd One last Quote for you. Have a nice live. :)");loadingDots();

     printf("\n\n\"The Road goes ever on and on");sleep_ms(2400);
     printf("\n Down from the door where it began");sleep_ms(2400);
     printf("\n Now far ahead the Road has gone");sleep_ms(2400);
     printf("\n And I must follow, if I can");sleep_ms(2400);
     printf("\n Pursuing it with eager feet");sleep_ms(2400);
     printf("\n Until it joins some larger way");sleep_ms(2400);
     printf("\n Where many paths and errands meet");sleep_ms(2400);
     printf("\n And whither then? I cannot say.\"");sleep_ms(2400);
     printf("\n  - J.R.R. Tolkien, Lord of the Rings\"\n\n");sleep_ms(2400);
}

void GameOver(GameState *game){
    //printf("Game Over\n");
    game->actualGame = 0;
    game->acceptInput = 0;
    stopMusic(game);
    startMusic(game, 1);
    addObjectTo_Array(game, game->currentRoom, 7, 9);//9
    sleep_ms(10000);
    done = 1;
}

void Blackscreen(GameState *game, int blackscreenTime, bool playAudio, int SoundID){
    //printf("Blackscreen\n");
    addObjectTo_Array(game, game->currentRoom, 7, 10);//10
    game->acceptInput = 0;
    if(playAudio){
        playSound(game, SoundID, 1);
    }
    sleep_ms(blackscreenTime);
    game->acceptInput = 1;
    removeObjectFrom_Array(game, game->currentRoom, 7, 10);//10
}
