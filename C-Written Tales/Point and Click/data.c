#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "letEmSpeak.h"
#include "audio.h"
#include "structDefinitions.h"
#include "dataOperations.h"
#include "dialogue.h"
#include "extras.h"


void sleep_ms(int milliseconds)
{
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
}



char imgSource[100][100]={
  {"img\\charToUp1.png"},//0
  {"img\\charToUp2.png"},//1
  {"img\\charToRight1.png"},//2
  {"img\\charToRight2.png"},//3
  {"img\\charToBottom1.png"},//4
  {"img\\charToBottom2.png"},//5
  {"img\\charToLeft1.png"},//6
  {"img\\charToLeft2.png"},//7
  {"img\\woodenFloor.png"},//8
  {"img\\wallWithoutWindow.png"},//9
  {"img\\wallWithWindow.png"},//10
  {"img\\oldCurtains2.png"},//11
  {"img\\oldCurtains1.png"},//12
  {"img\\backgroundTower.png"},//13
  {"img\\backgroundRiver.png"},//14
  {"img\\cagefloor.png"},//15
  {"img\\lock.png"},//16
  {"img\\bookshelf.png"},//17
  {"img\\cauldron 1.png"},//18
  {"img\\cauldron 2.png"},//19
  {"img\\cauldron 3.png"},//20
  {"img\\cauldron 4.png"},//21
  {"img\\crow.png"},//22
  {"img\\Door.png"},//23
  {"img\\shelfWithRatInIt.png"},//24
  {"img\\cat.png"},//25
  {"img\\darkPlace.png"},//26
  {"img\\candel.png"},//27
  {"img\\riverFrontPart.png"},//28
  {"img\\troll.png"},//29
  {"img\\fishingRod.png"},//30
  {"img\\skeletonArm.png"},//31
  {"img\\broom.png"},//32
  {"img\\cageKey.png"},//33
  {"img\\aliveRat.png"},//34
  {"img\\ratBrain.png"},//35
  {"img\\bowl.png"},//36
  {"img\\slime.png"},//37
  {"img\\flaskUnknownLiquid.png"},//38
  {"img\\gunPowder.png"},//39
  {"img\\mushroom.png"},//40
  {"img\\fuse.png"},//41
  {"img\\bombWithoutFuse.png"},//42
  {"img\\bomb.png"},//43
  {"img\\stickyBomb.png"},//44
  {"img\\stickyBurningBomb.png"},//45
  {"img\\magicalStuffTM1230.png"},//46
  {"img\\shelfKey.png"},//47
  {"img\\bigStone.png"},//48
  {"img\\hook.png"},//49
  {"img\\wormy.png"},//50
  {"img\\shovel.png"},//51
  {"img\\fishbone.png"},//52
  {"img\\wartsSecretion.png"},//53
  {"img\\bait.png"},//54
  {"img\\deadRat.png"},//55
  {"img\\cauldronEmpty.png"},//56
  {"img\\keyHolder.png"},//57
  {"img\\skeletonHead.png"},//58
  {"img\\witch.png"},//59
  {"img\\gameOver.png"},//60
  {"img\\blackscreen.png"},//61
  {"img\\inventoryBackground.png"},//62
  {"img\\mountedOnMouseIcon.png"},//63
  {"img\\cageForeground.png"},//64
  {"img\\bars.png"},//65
  {"img\\magicalDoor.png"},//66
  {"img\\notSoMagicalDoor.png"},//67
  {"img\\shelfWithRatOpen.png"},//68
  {"img\\riverForeground.png"},//69
  {"img\\broomInv.png"},//70
  {"img\\wayTower.png"},//71
  {"img\\dirt.png"},//72
  {"img\\signRiver.png"},//73
  {"img\\signTower.png"},//74
  {"img\\bushes.png"},//75
  {"img\\bookshelfNear.png"},//76
  {"img\\returnToRoom0.png"},//77
  {"img\\magicBook.png"},//78
  {"img\\triforce.png"},//79
  {"img\\theEnd.png"},//80
  {"img\\theBeginning.png"},//81
  {"img\\witchAnimation1.png"},//82
  {"img\\witchAnimation2.png"},//83
  {"img\\witchAnimation3.png"},//84
  {"img\\riverTreesForeground.png"},//85
  {"img\\startButton.png"}//86
  };

char musicSource[100][100]={
  {"music\\musik.wav"},//StartMusic
  {"music\\musik.wav"},//GameOverMusic
  {"music\\musik.wav"},//FinishedGameMusic
  {"music\\musik.wav"}//gameMusic
  };

char soundSource[150][100]={
  {"sounds\\dialogue0.wav"},//0
  {"sounds\\dialogue1.wav"},//1
  {"sounds\\dialogue2.wav"},//2
  {"sounds\\dialogue3.wav"},//3
  {"sounds\\dialogue4.wav"},//4
  {"sounds\\dialogue5.wav"},//5
  {"sounds\\dialogue6.wav"},//6
  {"sounds\\dialogue7.wav"},//7
  {"sounds\\dialogue8.wav"},//8
  {"sounds\\dialogue9.wav"},//9
  {"sounds\\dialogue10.wav"},//10
  {"sounds\\dialogue11.wav"},//11
  {"sounds\\dialogue12.wav"},//12
  {"sounds\\dialogue13.wav"},//13
  {"sounds\\dialogue14.wav"},//14
  {"sounds\\dialogue15.wav"},//15
  {"sounds\\dialogue16.wav"},//16
  {"sounds\\dialogue17.wav"},//17
  {"sounds\\dialogue18.wav"},//18
  {"sounds\\dialogue19.wav"},//19
  {"sounds\\dialogue20.wav"},//20
  {"sounds\\dialogue21.wav"},//21
  {"sounds\\dialogue22.wav"},//22
  {"sounds\\dialogue23.wav"},//23
  {"sounds\\dialogue24.wav"},//24
  {"sounds\\dialogue25.wav"},//25
  {"sounds\\dialogue26.wav"},//26
  {"sounds\\dialogue27.wav"},//27
  {"sounds\\dialogue28.wav"},//28
  {"sounds\\dialogue29.wav"},//29
  {"sounds\\dialogue30.wav"},//30
  {"sounds\\dialogue31.wav"},//31
  {"sounds\\dialogue32.wav"},//32
  {"sounds\\dialogue33.wav"},//33
  {"sounds\\dialogue34.wav"},//34
  {"sounds\\dialogue35.wav"},//35
  {"sounds\\dialogue36.wav"},//36
  {"sounds\\dialogue37.wav"},//37
  {"sounds\\dialogue38.wav"},//38
  {"sounds\\dialogue39.wav"},//39
  {"sounds\\dialogue40.wav"},//40
  {"sounds\\dialogue41.wav"},//41
  {"sounds\\dialogue42.wav"},//42
  {"sounds\\dialogue43.wav"},//43
  {"sounds\\dialogue44.wav"},//44
  {"sounds\\dialogue45.wav"},//45
  {"sounds\\dialogue46.wav"},//46
  {"sounds\\dialogue47.wav"},//47
  {"sounds\\dialogue48.wav"},//48
  {"sounds\\dialogue49.wav"},//49
  {"sounds\\dialogue50.wav"},//50
  {"sounds\\dialogue51.wav"},//51
  {"sounds\\dialogue52.wav"},//52
  {"sounds\\dialogue53.wav"},//53
  {"sounds\\dialogue54.wav"},//54
  {"sounds\\dialogue55.wav"},//55
  {"sounds\\dialogue56.wav"},//56
  {"sounds\\dialogue57.wav"},//57
  {"sounds\\dialogue58.wav"},//58
  {"sounds\\dialogue59.wav"},//59
  {"sounds\\dialogue60.wav"},//60
  {"sounds\\dialogue61.wav"},//61
  {"sounds\\dialogue62.wav"},//62
  {"sounds\\dialogue63.wav"},//63
  {"sounds\\dialogue64.wav"},//64
  {"sounds\\dialogue65.wav"},//65
  {"sounds\\dialogue66.wav"},//66
  {"sounds\\dialogue67.wav"},//67
  {"sounds\\dialogue68.wav"},//68
  {"sounds\\dialogue69.wav"},//69
  {"sounds\\dialogue70.wav"},//70
  {"sounds\\dialogue71.wav"},//71
  {"sounds\\dialogue72.wav"},//72
  {"sounds\\dialogue73.wav"},//73
  {"sounds\\dialogue74.wav"},//74
  {"sounds\\dialogue75.wav"},//75
  {"sounds\\dialogue76.wav"},//76
  {"sounds\\dialogue77.wav"},//77
  {"sounds\\dialogue78.wav"},//78
  {"sounds\\dialogue79.wav"},//79
  {"sounds\\dialogue80.wav"},//80
  {"sounds\\dialogue81.wav"},//81
  {"sounds\\dialogue82.wav"},//82
  {"sounds\\dialogue83.wav"},//83
  {"sounds\\dialogue84.wav"},//84
  {"sounds\\dialogue85.wav"},//85
  {"sounds\\dialogue86.wav"},//86
  {"sounds\\dialogue87.wav"},//87
  {"sounds\\dialogue88.wav"},//88
  {"sounds\\dialogue89.wav"},//89
  {"sounds\\dialogue90.wav"},//90
  {"sounds\\dialogue91.wav"},//91
  {"sounds\\dialogue92.wav"},//92
  {"sounds\\dialogue93.wav"},//93
  {"sounds\\dialogue94.wav"},//94
  {"sounds\\dialogue95.wav"},//95
  {"sounds\\dialogue96.wav"},//96
  {"sounds\\dialogue97.wav"},//97
  {"sounds\\dialogue98.wav"},//98
  {"sounds\\dialogue99.wav"},//99
  {"sounds\\dialogue100.wav"},//100
  {"sounds\\dialogue101.wav"},//101
  {"sounds\\dialogue102.wav"},//102
  {"sounds\\dialogue103.wav"},//103
  {"sounds\\dialogue104.wav"},//104
  {"sounds\\dialogue105.wav"},//105
  {"sounds\\dialogue106.wav"},//106
  {"sounds\\dialogue107.wav"},//107
  {"sounds\\dialogue108.wav"},//108
  {"sounds\\dialogue109.wav"},//109
  {"sounds\\dialogue110.wav"},//110
  {"sounds\\dialogue111.wav"},//111
  {"sounds\\dialogue112.wav"},//112
  {"sounds\\dialogue113.wav"},//113
  {"sounds\\dialogue114.wav"},//114
  {"sounds\\dialogue115.wav"},//115
  {"sounds\\dialogue116.wav"},//116
  {"sounds\\dialogue117.wav"},//117
  {"sounds\\dialogue118.wav"},//118
  {"sounds\\dialogue119.wav"},//119
  {"sounds\\dialogue120.wav"},//120
  {"sounds\\dialogue121.wav"},//121
  {"sounds\\dialogue122.wav"},//122
  {"sounds\\dialogue123.wav"},//123
  {"sounds\\dialogue124.wav"},//124
  {"sounds\\dialogue125.wav"},//125
  {"sounds\\dialogue126.wav"},//126
  {"sounds\\dialogue127.wav"},//127
  {"sounds\\dialogue128.wav"},//128
  {"sounds\\dialogue129.wav"},//129
  {"sounds\\dialogue130.wav"},//130
  {"sounds\\dialogue130.wav"},//131
  {"sounds\\dialogue131.wav"},//132
  {"sounds\\dialogue132.wav"},//133
  {"sounds\\dialogue133.wav"},//134
  {"sounds\\dialogue134.wav"},//135
  {"sounds\\dialogue135.wav"},//136
  {"sounds\\explosion.wav"},//137
  {"sounds\\attackingCat.wav"}//138
  };

int animationArray[100][15] = {
  {0,4,59,82,83,84},//0     // 1.Counter( !! MUST BE ZERO!! ) 2.Count of defined Values behind  3-15. ImageIDs

  };

char riddles[50][2][200]={
  {{"1, 2 , or 3"},{"2"}}//0
};

char texts[200][200]={
  {"The cage is locked. Without a key there is no way that I get out of this cage alive."},//0
  {"The cage is still locked."},//1
  {"Oh now the cage is unlocked... not. Do something useful and just stop."},//2
  {"I am starting to envy those pitiful heroes, whose developers were to lazy to give their protagonist the ability to speak!"},//3
  {"Normally I wouldn't touch something like this, but in a situation like this I will make an exception."},//4
  {"Yeah it's an skeleton arm. Now I have three arms."},//5
  {"This could come in handy. Or broomy? (Disclaimer: We're not proud of this joke)"},//6
  {"An ordinary broom."},//7
  {"Finally I can unlock this freaking lock."},//8
  {"A magical key. It opens the door into a fantasy land. With freedom. So basically a random key."},//9
  {"The lock cannot be opened without a key."},//10
  {"Maybe I should have listened at \"lock-picking 1 on 1\"   ... no it was worth it ;)."},//11
  {"So yeah it's useless without a key."},//12
  {"*knaaar* Finally! The cage was pretty small."},//13
  {"Krraaaar. Hello girl. Would you be so nice and bring me some food from the closet of the witch."},//14
  {"Kraaaaaaaaar. WITCH! THE GIRL ESCAPED! KILL HER!"},//15
  {"I will not scream like a little bitch and I will help you escaping this awful place."},//16
  {"Thank you! The closet is in the other room with the witch!"},//17
  {"Thank you! I appreciate the gesture. The witch is a mean witch and doesn't gives me enough food... "},//18
  {"Look in the bookshelf, inside there this a magic book that will help you to unlock the magic barrier."},//19
  {"Riddle: "},//20
  {"I will not talk to cage people!"},//21
  {"That is a pretty weird witch! I shouldn't wake her up or this will end ugly. Better be quiet.. and fast!"},//22
  {"Seems to be a magic mushroom. Could be useful."},//23
  {"Will I grow when I eat the magic mushroom? Or will I get a food poisoning... Not worth trying."},//24
  {"That seems to be a smart idea... What bad can happen in a dark, moist place under the bed of a witch.."},//25
  {"Hello darkness my old friend... oh no... copyright infringements..."},//26
  {"I would grab under the bed... but there is a weird substance... sooooo... no."},//27
  {"Yeah with to broom it works... Oh great a green slimy substance... Perfect for my new pocket... Thank you Tom.."},//28
  {"Hey a random flask with a random substance, another great idea! "},//29
  {"Finally something useful, the key for the closet."},//30
  {"I don't want to know what else is under the bed, so I will not risk anything else."},//31
  {"Why so slimy. "},//32
  {"A random flask with a weird substance... yeah what could go wrong..."},//33
  {"A key... Not everything is special."},//34
  {"Locked. Just Locked."},//35
  {"Wow! Inside this closet is everything I've ever wanted... And Tom...But I only can take out the birdfood."},//36
  {"The key magically disappeared... "},//37
  {"Ok the bird food is a living rat.. fine... Ouuuuh! It bit me!"},//38
  {"I could use this courtain cord... So I take it. Wait, wouldn't that be burglary?.... naaah who cares."},//39
  {"A courtain cord. I wonder for what I can use it."},//40
  {"It's a normal door. Sealed with magic. Epic. Like in an epic saga."},//41
  {"Always these fandom nerds."},//42
  {"So this magic paste removed the magic barrier. But now the door is glued together. Epic fail."},//43
  {"What could go wrong...."},//44
  {"After stiring water with the silmy substance,  use some brain while cooking and take some shrooms."},//45
  {"Sometimes two brains work faster then one."},//46
  {"It's a rat brain. Something everybody should have in his inventory."},//47
  {"It's a couldron with some water in it."},//48
  {"Green."},//49
  {"Orange."},//50
  {"Purple."},//51
  {"Seems to be ready."},//52
  {"I call it \"magical pasteTM  1230\""},//53
  {"Magic paste... Nothing more, nothing less. But a registered trademark."},//54
  {"A bowl is always useful."},//55
  {"Is it a pan? Is it a cup? NO! It's a \"super\"bowl!"},//56
  {"Why has a witch gunpowder? I confiscate it... For the greater good!"},//57
  {"I have some great ideas with this..."},//58
  {"It's dangerous to let a candle burn without supervision... Bad stuff can happen..."},//59
  {"Maybe I should have brought the candle to the bomb and not the bomb to the candle... too late. Better go fast."},//60
  {"The extra-arm came in \"handy\". (Again, we are ashamed!)"},//61
  {"I don't wont to talk about it. Just let it be!"},//62
  {"What an ugly witch. Everywhere are warts and she stinks like meat. Or childen. Same thing for her."},//63
  {"Maybe I should not spend too much time on her."},//64
  {"She can wake up anytime."},//65
  {"Let it be. Or let it go. Whichever company pays us more."},//66
  {"She felt our glances and woke up.... Game over."},//67
  {"It's a bomb without a fuse."},//68
  {"Crafting in progress..."},//69
  {"Now it has a fuse!"},//70
  {"Now it is sticky!"},//71
  {"Now it's burning. Maybe I should hurry. Really hurry!"},//72
  {"Why are you talking to me? You have a burning bomb in your hand!"},//73
  {"It isn't wise to talk to me, while you holding a burning bomb... Put it under the bed of the witch or somewhere else."},//74
  {"Don't give me the bomb stupid! USE IT ON THE DOOR!"},//75
  {"You are really not interesting... Go away!"},//76
  {"That was a stupid idea. Magic paste? Seriously?  "},//77
  {"Why you just don't make a bomb and destroy everything! "},//78
  {"Don't come near me with this flask...."},//79
  {"How did I survive... Nevertheless, the witch is hopefully dead and I am free!"},//80
  {"Seems to be a rocky road."},//81
  {"It's an rock. That blocks my way... Maybe I'll find a way."},//82
  {"Maybe Rock & Roll? Naah it's to heavy..."},//83
  {"It may be hard, but it is nevertheless no cafe, so maybe I should do something else?"},//84
  {"Hey that the rock has a sad face! Maybe I've touched him too much..."},//85
  {"Still a rock."},//86
  {"Wingardium Leviosaaaaa! Hm, spells from Hogwarts are useless here."},//87
  {"Nevertheless it's a rock."},//88
  {"What should I do with it? Put it into my pocket?"},//89
  {"It worked... Seriously?"},//90
  {"Yeah... So there is a stone, that it the bigger then me, in my pocket. Isn't it great that we are inside a Point 'n Click Adventure."},//91
  {"A hook-formed piece of metal. Could be useful."},//92
  {"It's a metalpiece with a interesting form."},//93
  {"Such an fresh and ungeneric idea for a place. There was somebody very creative."},//94
  {"Oh a shovel. Endless possibilities to use it. I could play golf, hit somebody with it, give it somebody as a gift. Endless!"},//95
  {"Endless possibilities!"},//96
  {"Under the stone is now some dirt, crawling with worms."},//97
  {"Oh I've got one! But the others escaped. Seems like they are pack animals. "},//98
  {"What a fun little guy, I'll call him wormy."},//99
  {"A fishing rod. Fishing... a interesting hobby. I prefer fishing for compliments."},//100
  {"So wormy, bring me luck! Perfect a piranha! Hey you cat survived? HEY! What are you doing, this my fish! STOP! "},//101
  {"And thats why dogs are better."},//102
  {"It seems to be a calm river..."},//103
  {"Oh no! I cannot pass the river, there are piranhas... What an original idea."},//104
  {"What a great idea. Maybe as great as this game..."},//105
  {"HUNGER! ELV! MAMPF!"},//106
  {"Hello my dear. Always nice to meet an intelligent colluquists so far away from the civilication."},//107
  {"I AM TOM! I EAT TO YOU WANT!"},//108
  {"Sorry my dear, my lovely brother is just very hungry and so just unbearable."},//109
  {"Maybe when you bring him something to eat, I'll let you pass."},//110
  {"Sorry my dear, but this isn't enough. It's hard to control my brother when he is hungry. So I cannot let you pass, for your safety."},//111
  {"PASS CANNOT YOU!"},//112
  {"So there is just only one more option left?"},//113
  {"Hello my dear troll? Maybe we can make an agreement..."},//114
  {"WHAT DO YOU MEAN?."},//115
  {"Sorry my dear, but we are not playing on your team... But maybe you could get us some meat..."},//116
  {"HUNGRY!"},//117
  {"Sorry my dear, without something to control my brother there is no way..."},//118
  {"Can I pass? Hmmmm nah."},//119
  {"Now? Nope."},//120
  {"Couldn't you just watch the fish? - I can, my brother not soo... mm"},//121
  {"Can I pass? YOU CANNOT PASS! eeeeeemhm"},//122
  {"Hello sweety - aahaah"},//123
  {"Now? Yes of cause my darling! Really? hmmnäää"},//124
  {"Do you eat leafs? hmnänänänä"},//125
  {"You're a womyn-hating, close-minded, imperialistic green-devil! - SJW generator? "},//126
  {"TEXT"},//127
  {"TEXT"},//128
  {"TEXT"},//129
  {"TEXT"},//130
  {"I'm sorry Wormy"},//131
  {"I should get nearer"},//132
  {"I can't imagine something to craft from these two."},//133
  {"Save not implemented"},//134
  {"TEXT"}//135
};

char questions[200][200]={
  {"1: Yeah... Sure. 2. No, never! You ugly-ass crow! 3.Would I get any advantage for doing that."},//0

};

int letEmSpeakArray[200][3]={
  {0, 0, 1500},//0     //1.SoundID 2.TextId 3.Delay in Milliseconds
  {0, 1, 1500},//1
  {0, 2, 1500},//2
  {0, 3, 1500},//3
  {0, 4, 1500},//4
  {0, 5, 1500},//5
  {0, 6, 1500},//6
  {0, 7, 1500},//7
  {0, 8, 1500},//8
  {0, 9, 1500},//9
  {0, 10, 1500},//10
  {0, 11, 1500},//11
  {0, 12, 1500},//12
  {0, 13, 1500},//13
  {0, 14, 1500},//14
  {0, 15, 1500},//15
  {0, 16, 1500},//16
  {0, 17, 1500},//17
  {0, 18, 1500},//18
  {0, 19, 1500},//19
  {0, 20, 1500},//20
  {0, 21, 1500},//21
  {0, 22, 1500},//22
  {0, 23, 1500},//23
  {0, 24, 1500},//24
  {0, 25, 1500},//25
  {0, 26, 1500},//26
  {0, 27, 1500},//27
  {0, 28, 1500},//28
  {0, 29, 1500},//29
  {0, 30, 1500},//30
  {0, 31, 1500},//31
  {0, 32, 1500},//32
  {0, 33, 1500},//33
  {0, 34, 1500},//34
  {0, 35, 1500},//35
  {0, 36, 1500},//36
  {0, 37, 1500},//37
  {0, 38, 1500},//38
  {0, 39, 1500},//39
  {0, 40, 1500},//40
  {0, 41, 1500},//41
  {0, 42, 1500},//42
  {0, 43, 1500},//43
  {0, 44, 1500},//44
  {0, 45, 1500},//45
  {0, 46, 1500},//46
  {0, 47, 1500},//47
  {0, 48, 1500},//48
  {0, 49, 1500},//49
  {0, 50, 1500},//50
  {0, 51, 1500},//51
  {0, 52, 1500},//52
  {0, 53, 1500},//53
  {0, 54, 1500},//54
  {0, 55, 1500},//55
  {0, 56, 1500},//56
  {0, 57, 1500},//57
  {0, 58, 1500},//58
  {0, 59, 1500},//59
  {0, 60, 1500},//60
  {0, 61, 1500},//61
  {0, 62, 1500},//62
  {0, 63, 1500},//63
  {0, 64, 1500},//64
  {0, 65, 1500},//65
  {0, 66, 1500},//66
  {0, 67, 1500},//67
  {0, 68, 1500},//68
  {0, 69, 1500},//69
  {0, 70, 1500},//70
  {0, 71, 1500},//71
  {0, 72, 1500},//72
  {0, 73, 1500},//73
  {0, 74, 1500},//74
  {0, 75, 1500},//75
  {0, 76, 1500},//76
  {0, 77, 1500},//77
  {0, 78, 1500},//78
  {0, 79, 1500},//79
  {0, 80, 1500},//80
  {0, 81, 1500},//81
  {0, 82, 1500},//82
  {0, 83, 1500},//83
  {0, 84, 1500},//84
  {0, 85, 1500},//85
  {0, 86, 1500},//86
  {0, 87, 1500},//87
  {0, 88, 1500},//88
  {0, 89, 1500},//89
  {0, 90, 1500},//90
  {0, 91, 1500},//91
  {0, 92, 1500},//92
  {0, 93, 1500},//93
  {0, 94, 1500},//94
  {0, 95, 1500},//95
  {0, 96, 1500},//96
  {0, 97, 1500},//97
  {0, 98, 1500},//98
  {0, 99, 1500},//99
  {0, 100, 1500},//100
  {0, 101, 1500},//101
  {0, 102, 1500},//102
  {0, 103, 1500},//103
  {0, 104, 1500},//104
  {0, 105, 1500},//105
  {0, 106, 1500},//106
  {0, 107, 1500},//107
  {0, 108, 1500},//108
  {0, 109, 1500},//109
  {0, 110, 1500},//110
  {0, 111, 1500},//111
  {0, 112, 1500},//112
  {0, 113, 1500},//113
  {0, 114, 1500},//114
  {0, 115, 1500},//115
  {0, 116, 1500},//116
  {0, 117, 1500},//117
  {0, 118, 1500},//118
  {0, 119, 1500},//119
  {0, 120, 1500},//120
  {0, 121, 1500},//121
  {0, 122, 1500},//122
  {0, 123, 1500},//123
  {0, 124, 1500},//124
  {0, 125, 1500},//125
  {0, 126, 1500},//126
  {0, 127, 1500},//127
  {0, 128, 1500},//128
  {0, 129, 1500},//129
  {0, 130, 1500},//130
  {0, 131, 1500},//131
  {0, 132, 1500},//132
  {0, 133, 1500},//133
  {0, 134, 1500},//134
  {0, 135, 1500},//135
};

int EVENTID;
int CLICKCOUNT;
GameState *GAME;
int OBJEKTID;
pthread_t PTHREAD_HANDLE;


void loadRenderedObjects(GameState *game){
//fillRenderedObjects(game, 0/*INDEX*/, 550/*ID*/, 100/*X*/, 100/*Y*/, 100/*Width*/,100/*Height*/, 0/*imgID*/);
fillRenderedObjects(game, 0, 0, 0, 337, 1200, 337, 8);
fillRenderedObjects(game, 1, 1, 0, 0, 1200, 337, 9);
fillRenderedObjects(game, 2, 2, 0, 0, 1200,337, 10);
fillRenderedObjects(game, 3, 3, 460, 45, 290, 200, 11);
fillRenderedObjects(game, 4, 4, 0, 0, 1200,337, 13);
fillRenderedObjects(game, 5, 5, 0, 0, 1200,337, 14);
fillRenderedObjects(game, 6, 6, 10, 250, 250,250, 56);
fillRenderedObjects(game, 7, 7, 550, 70, 50,50, 57);
fillRenderedObjects(game, 8, 8, 1070, 430, 40,40, 58);
fillRenderedObjects(game, 9, 9, 0, 0, 1200,800, 60);
fillRenderedObjects(game, 10, 10, 0, 0, 1200,800, 61);
fillRenderedObjects(game, 11, 11, 810, 120, 300, 400, 64);
fillRenderedObjects(game, 12, 12, 0, 0, 1200, 675, 65);
fillRenderedObjects(game, 13, 13, 0, 337, 1200, 337, 71);
fillRenderedObjects(game, 14, 14, 0, 337, 1200, 337, 69);
fillRenderedObjects(game, 15, 15, 0, 375, 500, 300, 75);
fillRenderedObjects(game, 16, 16, 0, 0, 1200, 675, 76);
fillRenderedObjects(game, 17, 17, 0, 0, 1200, 800, 80);
fillRenderedObjects(game, 18, 18, 0, 0, 1200, 800, 81);
fillRenderedObjects(game, 19, 19, 0, 0, 1200, 800, 85);
//fillRenderedObjects(game, 0, 550, 100, 100, 100,100, 0);
}

void loadInteractiveRenderedObjects(GameState *game){
fillInteractiveRenderedObjects(game, 0/*INDEX*/, 550/*ID*/, 100/*X*/, 100/*Y*/, 100/*Width*/,100/*Height*/, 0/*imgID*/,
                               false/*clickable*/, 0/*clickCount*/, 0/*EventId*/, false/*InteractiveWithObject*/,
                                0/*IdOfNeededObjectToInteract*/, false/*OnlyUsableWhenNear*/, 0/*InteractionEventID*/, 0/*InteractionEventCount*/);

fillInteractiveRenderedObjects(game, 0, 300, 810, 120, 300, 400, 15, true, 0, 1, false,  0, false, 0,  0);
fillInteractiveRenderedObjects(game, 1, 301, 810, 350, 45, 55, 16, true, 0, 2, true,  552, false, 200,  0);
fillInteractiveRenderedObjects(game, 2, 302, 200, 85, 360, 300, 17, true, 0, 3, false,  0, true, 0,  0);
fillInteractiveRenderedObjects(game, 3, 303, 10, 250, 250, 250, 18, true, 0, 4, true,  556, true, 201,  0);
fillInteractiveRenderedObjects(game, 4, 304, 10, 250, 250, 250, 19, true, 0, 5, true,  554, true, 202,  0);
fillInteractiveRenderedObjects(game, 5, 305, 10, 250, 250, 250, 20, true, 0, 6, true,  559, true, 203,  0);
fillInteractiveRenderedObjects(game, 6, 306, 10, 250, 250, 250, 21, true, 0, 7, true,  555, true, 204,  0);
fillInteractiveRenderedObjects(game, 7, 307, 1100, 50, 100, 100, 22, true, 0, 8, true,  553, false, 205,  0);
fillInteractiveRenderedObjects(game, 8, 308, 600, 0, 240, 350, 23, true, 0, 9, false,  0, true, 0,  0);
fillInteractiveRenderedObjects(game, 9, 309, 1050, 20, 135, 400, 24, true, 0, 10, true,  566, true, 217,  0);
fillInteractiveRenderedObjects(game, 10, 310, 20, 530, 160, 110, 25, true, 0, 11, false,  0, false, 0,  0);
fillInteractiveRenderedObjects(game, 11, 311, 260, 310, 350, 40, 26, true, 0, 12, true,  551, true, 206,  0);
fillInteractiveRenderedObjects(game, 12, 312, 810, 0, 240, 350, 23, true, 0, 13, true,  0, true, 0,  0);
fillInteractiveRenderedObjects(game, 13, 313, 670, 190, 60, 100, 27, true, 0, 14, true,  563, true, 208,  0);
fillInteractiveRenderedObjects(game, 14, 314, 800, 337, 280, 337, 28, true, 0, 15, true,  567, false, 209,  0);
fillInteractiveRenderedObjects(game, 15, 315, 650, 200, 200, 250, 29, true, 0, 16, true,  571, true, 210,  0);
fillInteractiveRenderedObjects(game, 16, 316, 780, 400, 114, 250, 30, true, 0, 17, true,  573, true, 211,  0);
fillInteractiveRenderedObjects(game, 17, 317, 500, 400, 200, 125, 72, true, 0, 42, true,  570, true, 212,  0);
fillInteractiveRenderedObjects(game, 18, 318, 0, 0, 24, 103, 31, true, 0, 43, false,  0, false, 0,  0);
fillInteractiveRenderedObjects(game, 19, 319, 560, 180, 40, 200, 32, true, 0, 44, true,  550, false, 213,  0);
fillInteractiveRenderedObjects(game, 20, 320, 570, 90, 30, 75, 33, true, 0, 45, true,  551, false, 214,  0);
fillInteractiveRenderedObjects(game, 21, 321, 1050, 500, 100, 40, 55, true, 0, 46, false,  0, true, 215,  0);
fillInteractiveRenderedObjects(game, 22, 322, 460, 45, 290, 200, 12, true, 0, 47, false,  0, true, 0,  0);
fillInteractiveRenderedObjects(game, 23, 323, 260, 175, 350, 175, 59, true, 0, 48, true,  550, true, 216,  0);
fillInteractiveRenderedObjects(game, 24, 324, 557, 488, 36, 97, 78, true, 0, 49, false,  0, false, 0,  0);//magicBook
fillInteractiveRenderedObjects(game, 25, 325, 10, 0, 240, 350, 66, true, 0, 50, true,  565, true, 218,  0);
fillInteractiveRenderedObjects(game, 26, 326, 10, 0, 240, 350, 67, true, 0, 51, true,  564, true, 219,  0);
fillInteractiveRenderedObjects(game, 27, 327, 950, 180, 200, 200, 73, true, 0, 52, false, 0, true, 0,  0);
fillInteractiveRenderedObjects(game, 28, 328, 200, 200, 200, 200, 74, true, 0, 53, false, 0, true, 0,  0);
fillInteractiveRenderedObjects(game, 29, 329, 500, 300, 300, 300, 20/*86*/, true, 0, 58, false, 0, false, 0, 0); //Start
fillInteractiveRenderedObjects(game, 30, 330, 0, 0, 100, 100, 77, true, 0, 59, false, 0, false, 0, 0);//Return to room 0
fillInteractiveRenderedObjects(game, 31, 331, 420, 70, 150, 108, 79, true, 0, 60, false, 0, false, 0, 0);//triforce
}

void loadCollectibles(GameState *game)
{
    //fillCollectibleObjects(game, 0/*INDEX*/, 550/*ID*/, 100/*X*/, 100/*Y*/, 100/*Width*/,100/*Height*/, 0/*imgID*/,
    //false/*clickable*/, 0/*clickCount*/, 0/*EventId*/, false/*ableToCraft*/,
    //0/*idOFNeededObjectToCraft*/, false/*OnlyUsableWhenNear*/,0/*CraftEventID*/, 0 /*CraftEventCount*/);


    fillCollectibleObjects(game, 0, 550, 820, 450, 100, 50, 31, true, 0, 18, false, 0, false, 0, 0);                          //Skelettarm

    fillCollectibleObjects(game, 1, 551, 560, 180, 40, 200, 70, true, 0, 19, false, 0, false, 0, 0);                           //Besen

    fillCollectibleObjects(game, 2, 552, 100, 100, 6, 15, 33, true, 0, 20, false, 0, false, 0, 0);                            //Käfigschlüssel

    fillCollectibleObjects(game, 3, 553, 100, 100, 50, 20, 34, true, 0, 21, false, 0, false, 0, 0);                           //Lebende Ratte

    fillCollectibleObjects(game, 4, 554, 100, 100, 10, 10, 35, true, 0, 22, false, 0, false, 0, 0);                           //Rattenhirn

    fillCollectibleObjects(game, 5, 555, 605, 385, 100, 100, 36, true, 0, 23, false, 0, false, 0, 0);                           //Schale

    fillCollectibleObjects(game, 6, 556, 100, 100, 32, 32, 37, true, 0, 24, false, 0, false, 0, 0);                           //Schleim

    fillCollectibleObjects(game, 7, 557, 100, 100, 27, 27, 38, true, 0, 25, true, 558, false, 100, 0);                        //Flasche unknown liquid

    fillCollectibleObjects(game, 8, 558, 235, 538, 50, 50, 39, true, 0, 26, true, 557, false, 101, 0);                        //Schwarzpulver

    fillCollectibleObjects(game, 9, 559, 1130, 600, 67, 67, 40, true, 0, 27, false, 0, true, 0, 0);                            //Pilz

    fillCollectibleObjects(game, 10, 560, 100, 100, 32, 32, 41, true, 0, 28, true, 561, false, 102, 0);                       //gardinenKordel

    fillCollectibleObjects(game, 11, 561, 100, 100, 32, 32, 42, true, 0, 29, true, 560, false, 103, 0);                       //bomb without Fuse

    fillCollectibleObjects(game, 12, 562, 100, 100, 32, 32, 43, true, 0, 30, true, 572, false, 104, 0);                          //bomb

    fillCollectibleObjects(game, 13, 563, 100, 100, 32, 32, 44, true, 0, 31, true, 0, false, 0, 0);                       //sticky bombe

    fillCollectibleObjects(game, 14, 564, 100, 100, 32, 32, 45, true, 0, 32, false, 0, false, 0, 0);                          //sticky burning bomb

    fillCollectibleObjects(game, 15, 565, 100, 100, 32, 32, 46, true, 0, 33, false, 0, false, 0, 0);                          //magical stuff TM1230

    fillCollectibleObjects(game, 16, 566, 100, 100, 32, 32, 47, true, 0, 34, false, 0, false, 0, 0);                          //Schrankschlüssel

    fillCollectibleObjects(game, 17, 567, 375, 225, 450, 450, 48, true, 0, 35, false, 0, false, 0, 0);                         //big Stone

    fillCollectibleObjects(game, 18, 568, 100, 600, 40, 40, 49, true, 0, 36, true, 569, true, 105, 0);                        //metallstück

    fillCollectibleObjects(game, 19, 569, 100, 100, 32, 32, 50, true, 0, 37, true, 568, true, 106, 0);                        //Würme

    fillCollectibleObjects(game, 20, 570, 270, 490, 45, 180, 51, true, 0, 38, false, 0, true, 0, 0);                         //Schaufel

    fillCollectibleObjects(game, 21, 571, 100, 100, 32, 32, 52, true, 0, 39, false, 0, false, 0, 0);                          //fischgräten

    fillCollectibleObjects(game, 22, 572, 100, 100, 32, 32, 53, true, 0, 40, true, 562, false, 107, 0);                       //Warzensekret

    fillCollectibleObjects(game, 23, 573, 100, 100, 32, 32, 54, true, 0, 41, false, 0, false, 0, 0);                          //Köder
}



void loadGameInMemory(GameState *game){
    loadRenderedObjects(game);
    loadInteractiveRenderedObjects(game);
    loadCollectibles(game);
}

int *buffercurrentlyOnDisplay;
int **currentlyOnDisplay;
int *bufferAllowedToWalkHere;
int **AllowedToWalkHere;

void loadMenu(GameState *game){
    //Room 9
    //Hintergrund
    addObjectTo_Array(game, 9, 0, 18);
    addObjectTo_Array(game, 9, 2, 329);
    startMusic(game, 0);
}


void loadBeginning(GameState *game){
   // game->actualGame = 1;
    game->person.x = 850;
    game->person.y = 160;
//x = 850
//y = 160

    //startMusic(game, 0);

    //Room 0
    //Hintergrund
    addObjectTo_Array(game, 0, 0, 0);
    addObjectTo_Array(game, 0, 1, 1);
    addObjectTo_Array(game, 0, 1 ,300);//
    addObjectTo_Array(game, 0, 6, 11);
    //Foreground
    addObjectTo_Array(game, 0, 6, 12);
    //Items
    addObjectTo_Array(game, 0, 2, 8);
    addObjectTo_Array(game, 0, 2, 550);
    addObjectTo_Array(game, 0, 2, 301);//
    addObjectTo_Array(game, 0, 1, 302);
    addObjectTo_Array(game, 0, 1, 308);
    addObjectTo_Array(game, 0, 1, 319);
    addObjectTo_Array(game, 0, 1, 6);
    addObjectTo_Array(game, 0, 2, 303);
    addObjectTo_Array(game, 0, 1, 307);

    addObjectTo_Array(game, 0, 2, 7);
    addObjectTo_Array(game, 0, 3, 320);

    //Room 1 - Bookshelf
    addObjectTo_Array(game, 1, 2, 16);
    addObjectTo_Array(game, 1, 3, 330);
    addObjectTo_Array(game, 1, 4, 324);
    addObjectTo_Array(game, 1, 4, 558);
    addObjectTo_Array(game, 1, 4, 555);

    //Room2
    addObjectTo_Array(game, 2, 0, 0);
    addObjectTo_Array(game, 2, 1, 2);
    addObjectTo_Array(game, 2, 2, 312);
    addObjectTo_Array(game, 2, 2, 309);
    addObjectTo_Array(game, 2, 3, 323);
    addObjectTo_Array(game, 2, 3, 311);
    addObjectTo_Array(game, 2, 4, 313);
    addObjectTo_Array(game, 2, 2, 559);
    addObjectTo_Array(game, 2, 2, 322);
    addObjectTo_Array(game, 2, 2, 310);
    addObjectTo_Array(game, 2, 2, 325);
    addObjectTo_LoopAnimations(game, 323, 0);
    //Foreground
    addObjectTo_Array(game, 2, 6, 12);


    //Room 3 - Tower
    addObjectTo_Array(game, 3, 0, 13);
    addObjectTo_Array(game, 3, 1, 4);
    addObjectTo_Array(game, 3, 2, 317);
    addObjectTo_Array(game, 3, 2, 568);
    addObjectTo_Array(game, 3, 2, 327);
    addObjectTo_Array(game, 3, 3, 567);
    addObjectTo_Array(game, 3, 2, 331);
    //Foreground
   // addObjectTo_Array(game, 3, 6, 12);


   //Room 4 - River
    addObjectTo_Array(game, 4, 0, 14);
    addObjectTo_Array(game, 4, 1, 5);
    addObjectTo_Array(game, 4, 2, 314);
    addObjectTo_Array(game, 4, 2, 315);
    addObjectTo_Array(game, 4, 5, 316);
    addObjectTo_Array(game, 4, 5, 570);
    addObjectTo_Array(game, 4, 2, 328);
    addObjectTo_Array(game, 4, 6, 15);
    addObjectTo_Array(game, 4, 7, 19);
    //Foreground

    //Room 5 - The End
    addObjectTo_Array(game, 5, 0, 17);




}

void changeClickCountOfObject(GameState *game, int objektID, int newClickCount){

                if(objektID >= 300 && objektID < 550){
                   game->interactiveRenderedObjects[objektID-300].clickCount = newClickCount;
                }

                if(objektID >= 550){
                   game->collectibleObjects[objektID-550].clickCount = newClickCount;
                }
}

void changeInteraction_CRAFT_EventCountOfObject(GameState *game, int objektID, int newInteractionEventCount){

                if(objektID >= 300 && objektID < 550){
                   game->interactiveRenderedObjects[objektID-300].InteractionEventCount = newInteractionEventCount;
                }

                if(objektID >= 550){
                   game->collectibleObjects[objektID-550].CraftEventCount = newInteractionEventCount;
                }
}

void changeClickableOfObject(GameState *game, int objektID, bool clickable){

                if(objektID >= 300 && objektID < 550){
                   game->interactiveRenderedObjects[objektID-300].clickable = clickable;
                }

                if(objektID >= 550){
                   game->collectibleObjects[objektID-550].clickable = clickable;
                }
}

void handleEventId_1(GameState *game, int EventId, int clickCount, int objektID){
	if(EventId == 1){
		if(clickCount == 0){
                letEmSpeak(game, 0);
                changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
                letEmSpeak(game, 1);
                changeClickCountOfObject(game, objektID, 2);
		} else if(clickCount == 2){
                letEmSpeak(game, 2);
                changeClickCountOfObject(game, objektID, 3);
		} else if(clickCount == 3){
                letEmSpeak(game, 3);
                changeClickCountOfObject(game, objektID, 4);
                changeClickableOfObject(game, objektID, false);
		}
	}
    if(EventId == 2){
		if(clickCount == 0){
                letEmSpeak(game, 10);
                changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
                letEmSpeak(game, 11);
                changeClickCountOfObject(game, objektID, 2);
		} else if(clickCount == 2){
                letEmSpeak(game, 12);
		}
    }
	if(EventId == 3){
		if(clickCount == 0){
            game->acceptNoArrowInput = 1;
            game->currentRoom = 1;
            game->person.x = 1200;
            game->person.y = 675;
            while(game->currentRoom == 1 && game->interactiveRenderedObjects[24].clickCount == 0){
                    if(game->currentRoom == 1 && game->interactiveRenderedObjects[24].clickCount == 0){
                        addTextToShow(game,"Starting from the third sailor book, follow the flames, climb the vines, ...");
                        sleep_ms(5000);
                    }
                    if(game->currentRoom == 1 && game->interactiveRenderedObjects[24].clickCount == 0){
                        addTextToShow(game,"... wander to the wheat, go to the first of the pentalogy, hear the song of the wind, ...");
                        sleep_ms(5000);
                    }
                    if(game->currentRoom == 1 && game->interactiveRenderedObjects[24].clickCount == 0){
                        addTextToShow(game,"... follow the smell of iron and drop onto the magic book.");
                        sleep_ms(5000);
                    }

                deleteTextToShow(game);
            }

		}
	}
	if(EventId == 4){
		if(clickCount == 0){
            letEmSpeak(game, 48);
		}
	}
	if(EventId == 5){
		if(clickCount == 0){
            letEmSpeak(game, 49);
		}
	}
	if(EventId == 6){
		if(clickCount == 0){
            letEmSpeak(game, 50);
		}
	}
	if(EventId == 7){
		if(clickCount == 0){
            letEmSpeak(game, 51);
            changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
            letEmSpeak(game, 52);
		}
	}
	if(EventId == 8){
        if(clickCount == 0){
            letEmSpeak(game, 21);
        }
        if(clickCount == 1){
            letEmSpeak(game, 14);
            int answer = startGetAnswerToQuestion(game, 0);
            if(answer == 1){
                changeClickCountOfObject(game, objektID, 2);
            }
            if(answer == 2){
                letEmSpeak(game, 15);
                GameOver(game);

            }
            if(answer == 3){
                letEmSpeak(game, 16);
                changeClickCountOfObject(game, objektID, 2);
            }
        } else if(clickCount == 2){
                letEmSpeak(game,17);
        } else if(clickCount == 10){
                letEmSpeak(game,73);
        }
	}
	if(EventId == 9){
		if(clickCount == 0){
                game->currentRoom = 2;
                Blackscreen(game, 700,false,0);
                game->person.x = 850;
                game->person.y = 90;
                letEmSpeak(game, 22);
                changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
                game->currentRoom = 2;
                Blackscreen(game, 700,false,0);
                game->person.x = 850;
                game->person.y = 90;
		}
	}
	if(EventId == 10){
      if(clickCount == 0){
        letEmSpeak(game, 35);
      }
	}
	if(EventId == 11){
      if(clickCount == 0){
        letEmSpeak(game, 76);
      } else if(clickCount == 1){
        letEmSpeak(game, 77);
        changeClickCountOfObject(game, objektID, 2);
      } else if(clickCount == 2){
        letEmSpeak(game, 78);
        changeClickCountOfObject(game, objektID, 3);
      } else if(clickCount == 3){
        letEmSpeak(game, 79);
      } else if(clickCount == 10){
        letEmSpeak(game, 75);
      }
	}
	if(EventId == 12){
		if(clickCount == 0){
                letEmSpeak(game, 25);
                changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
                letEmSpeak(game, 26);
                changeClickCountOfObject(game, objektID, 2);
		} else if(clickCount == 2){
                letEmSpeak(game, 27);
                changeClickCountOfObject(game, objektID, 3);
		} else if(clickCount == 3){
                letEmSpeak(game, 28);
		}
	}
if(EventId == 13){
		if(clickCount == 0){
                game->currentRoom = 0;
                Blackscreen(game, 700,false,0);
                game->person.x = 660;
                game->person.y = 90;
		}
	}
if(EventId == 14){
		if(clickCount == 0){
            letEmSpeak(game, 59);
		}
	}
if(EventId == 15){
		if(clickCount == 0){
            letEmSpeak(game, 103);
            changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
		    letEmSpeak(game, 104);
		}
	}
if(EventId == 16){
		if(clickCount == 0){
            letEmSpeak(game, 106);
            changeClickCountOfObject(game, objektID, 1);
		} else if(clickCount == 1){
		    letEmSpeak(game, 107);
		    letEmSpeak(game, 108);
		    changeClickCountOfObject(game, objektID, 2);
		} else if(clickCount == 2){
		    letEmSpeak(game, 109);
		    letEmSpeak(game, 110);
		}  else if(clickCount == 3){
		    letEmSpeak(game, 114);
		    letEmSpeak(game, 115);
		    letEmSpeak(game, 116);
		    changeClickCountOfObject(game, objektID, 4);
		} else if(clickCount == 4){
		    letEmSpeak(game, 117);
		    changeClickCountOfObject(game, objektID, 5);
		} else if(clickCount == 5){
		    letEmSpeak(game, 118);
		    changeClickCountOfObject(game, objektID, 6);
		} else if(clickCount == 6){
		    letEmSpeak(game, 119);
		    changeClickCountOfObject(game, objektID, 7);
		} else if(clickCount == 7){
		    letEmSpeak(game, 120);
		    changeClickCountOfObject(game, objektID, 8);
		} else if(clickCount == 8){
		    letEmSpeak(game, 121);
		    changeClickCountOfObject(game, objektID, 9);
		} else if(clickCount == 9){
		    letEmSpeak(game, 122);
		    changeClickCountOfObject(game, objektID, 10);
		} else if(clickCount == 10){
		    letEmSpeak(game, 123);
		    changeClickCountOfObject(game, objektID, 11);
		} else if(clickCount == 11){
		    letEmSpeak(game, 124);
		    changeClickCountOfObject(game, objektID, 12);
		} else if(clickCount == 12){
		    letEmSpeak(game, 125);
		    changeClickCountOfObject(game, objektID, 13);
		} else if(clickCount == 13){
		    letEmSpeak(game, 126);
		    changeClickCountOfObject(game, objektID, 14);
		} else if(clickCount == 14){
		    letEmSpeak(game, 127);
		    changeClickCountOfObject(game, objektID, 15);
		} else if(clickCount == 15){
		    letEmSpeak(game, 128);
		    changeClickCountOfObject(game, objektID, 16);
		} else if(clickCount == 16){
		    letEmSpeak(game, 129);
		    changeClickCountOfObject(game, objektID, 17);
		} else if(clickCount == 17){
		    letEmSpeak(game, 130);
		    changeClickCountOfObject(game, objektID, 14);
		}

	}
if(EventId == 17){
      if(clickCount == 0){
        letEmSpeak(game, 100);
        }
	}
if(EventId == 18){
      if(clickCount == 0){
        letEmSpeak(game, 4);
        addObjectTo_ObjectsInInventory(game, 550);
        removeFromGameDisplay(game, 0, 550);
        changeClickCountOfObject(game, 550, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 5);
        //changeClickCountOfObject(game, objektID, 2);
		}
	}
if(EventId == 19){
      if(clickCount == 0){
        letEmSpeak(game, 7);
      }
	}
if(EventId == 20){
      if(clickCount == 0){
        letEmSpeak(game, 9);
      }
	}
if(EventId == 21){
      if(clickCount == 0){
        letEmSpeak(game, 38);
      }
	}
if(EventId == 22){
      if(clickCount == 0){
        letEmSpeak(game, 47);
      }
	}
if(EventId == 23){
      if(clickCount == 0){
        letEmSpeak(game, 55);
        changeClickCountOfObject(game, objektID, 1);
        removeFromGameDisplay(game, 1, 555);
        addObjectTo_ObjectsInInventory(game, 555);
      } else if(clickCount == 1){
        letEmSpeak(game, 56);
      }
	}
if(EventId == 24){
      if(clickCount == 0){
        letEmSpeak(game, 32);
      }
	}
if(EventId == 25){
      if(clickCount == 0){
        letEmSpeak(game, 33);
      }
	}
if(EventId == 26){
      if(clickCount == 0){
        letEmSpeak(game, 57);
        changeClickCountOfObject(game, clickCount, 1);
        removeFromGameDisplay(game, 1, 558);
        addObjectTo_ObjectsInInventory(game, 558);
      } else if(clickCount == 1){
        letEmSpeak(game, 58);
      }
	}
if(EventId == 27){
      if(clickCount == 0){
        letEmSpeak(game, 23);
        addObjectTo_ObjectsInInventory(game, 559);
        removeFromGameDisplay(game, 2, 559);
        changeClickCountOfObject(game, 559, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 24);
        //changeClickCountOfObject(game, objektID, 2);
		}
	}
if(EventId == 28){
      if(clickCount == 0){
        letEmSpeak(game, 40);
      }
	}
if(EventId == 29){
      if(clickCount == 0){
        letEmSpeak(game, 68);
      }
	}
if(EventId == 30){
      if(clickCount == 0){
        letEmSpeak(game, 70);
      }
	}
if(EventId == 31){
      if(clickCount == 0){
        letEmSpeak(game, 71);
      }
	}
if(EventId == 32){
      if(clickCount == 0){
        letEmSpeak(game, 72);
      }
	}
if(EventId == 33){
      if(clickCount == 0){
        letEmSpeak(game, 54);
      }
	}
if(EventId == 34){
      if(clickCount == 0){
        letEmSpeak(game, 34);
      }
	}
if(EventId == 35){
      if(clickCount == 0){
        letEmSpeak(game, 81);
        changeClickCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 82);
        changeClickCountOfObject(game, objektID, 2);
      } else if(clickCount == 2){
        letEmSpeak(game, 83);
        changeClickCountOfObject(game, objektID, 3);
      } else if(clickCount == 3){
        letEmSpeak(game, 84);
        changeClickCountOfObject(game, objektID, 4);
      } else if(clickCount == 4){
        letEmSpeak(game, 85);
        changeClickCountOfObject(game, objektID, 5);
      } else if(clickCount == 5){
        letEmSpeak(game, 86);
        changeClickCountOfObject(game, objektID, 6);
      } else if(clickCount == 6){
        letEmSpeak(game, 87);
        changeClickCountOfObject(game, objektID, 7);
      } else if(clickCount == 7){
        letEmSpeak(game, 88);
        changeClickCountOfObject(game, objektID, 8);
      } else if(clickCount == 8){
        letEmSpeak(game, 89);
        changeClickCountOfObject(game, objektID, 9);
      } else if(clickCount == 9){
        removeFromGameDisplay(game, 3, 567);
        addObjectTo_ObjectsInInventory(game, 567);
        letEmSpeak(game, 90);
        changeClickCountOfObject(game, objektID, 10);
      } else if(clickCount == 10){
        letEmSpeak(game, 91);
      }
	}
if(EventId == 36){
      if(clickCount == 0){
        letEmSpeak(game, 92);
        removeFromGameDisplay(game, 3, 568);
        addObjectTo_ObjectsInInventory(game, 568);
        changeClickCountOfObject(game, objektID, 1);
      } else if (clickCount == 1){
        letEmSpeak(game, 93);
        changeClickCountOfObject(game, objektID, 1);
      }
	}
if(EventId == 37){
      if(clickCount == 0){
        letEmSpeak(game, 99);
        }
	}
if(EventId == 38){
      if(clickCount == 0){
        removeFromGameDisplay(game, 4, 570);
        addObjectTo_ObjectsInInventory(game, 570);
        letEmSpeak(game, 95);
        changeClickCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
          letEmSpeak(game, 96);
      }
	}
if(EventId == 39){
      if(clickCount == 0){
        letEmSpeak(game, 102);
        }
	}
if(EventId == 40){
      if(clickCount == 0){
        letEmSpeak(game, 62);
      }
	}
if(EventId == 41){
      if(clickCount == 0){
        letEmSpeak(game, 131);
      }
	}
if(EventId == 42){
      if(clickCount == 0){
        letEmSpeak(game, 97);
      }
	}
if(EventId == 46){
      if(clickCount == 0){
        letEmSpeak(game, 46);
        addObjectTo_ObjectsInInventory(game, 554);
        changeClickableOfObject(game, objektID, false);
      }
	}
if(EventId == 47){
      if(clickCount == 0){
        letEmSpeak(game, 39);
        addObjectTo_ObjectsInInventory(game, 560);
        addObjectTo_Array(game, 2, 2, 3);
      }
	}
if(EventId == 48){
      if(clickCount == 0){
        letEmSpeak(game, 63);
        changeClickCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 64);
        changeClickCountOfObject(game, objektID, 2);
      } else if(clickCount == 2){
        letEmSpeak(game, 65);
        changeClickCountOfObject(game, objektID, 3);
      } else if(clickCount == 3){
        letEmSpeak(game, 66);
        changeClickCountOfObject(game, objektID, 4);
      } else if(clickCount == 4){
        letEmSpeak(game, 67);
        GameOver(game);
      }
	}
if(EventId == 49){
      if(clickCount == 0){
        changeClickCountOfObject(game, 324, 1);
        letEmSpeak(game, 45);
      } else if(clickCount == 1){
        letEmSpeak(game, 45);
      } else if(clickCount == 10){
        letEmSpeak(game, 74);
      }
	}
if(EventId == 50){
      if(clickCount == 0){
        letEmSpeak(game, 41);
      }
	}
if(EventId == 51){

	}
if(EventId == 52){
      if(clickCount == 0){
        letEmSpeak(game, 94);
        game->currentRoom = 4;
        Blackscreen(game, 700,false,0);
        game->person.x = 50;
        game->person.y = 200;
        game->person.imgID = 3;
        changeClickCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
        game->currentRoom = 4;
        Blackscreen(game, 700,false,0);
        game->person.x = 50;
        game->person.y = 200;
        game->person.imgID = 3;
      }
	}
if(EventId == 53){
      if(clickCount == 0){
        game->currentRoom = 3;
        Blackscreen(game, 700,false,0);
        game->person.x = 950;
        game->person.y = 200;
        game->person.imgID = 7;
      }
	}
if(EventId == 54){
      if(clickCount == 10){
        letEmSpeak(game, 105);
        game->actualGame = 0;
        Blackscreen(game, 2000, false, 0);
        game->currentRoom = 5;
        startMusic(game, 2);
      }
	}
if(EventId == 55){
      if(clickCount == 0){
        letEmSpeak(game, 132);
      }
	}
if(EventId == 56){
      if(clickCount == 0){
        letEmSpeak(game, 133);
      }
	}
if(EventId == 57){
      if(clickCount == 0){
        letEmSpeak(game, 134);
      }
	}
if(EventId == 58){
      if(clickCount == 0){
        game->currentRoom = 0;
        game->actualGame = 1;
        stopMusic(game);
        startMusic(game, 3);
      }
	}
if(EventId == 59){
      if(clickCount == 0){
        game->acceptNoArrowInput = 0;
        game->person.x = 320;
        game->person.y = 150;
        game->currentRoom = 0;
      }
	}
if(EventId == 60){
      if(clickCount == 0){
        letEmSpeak(game, 42);
      }
	}
}


void handleEventId_2(GameState *game, int EventId, int clickCount, int objektID){
    if(EventId == 100){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 558);
        removeObjectFrom_ObjectsInInventory(game, 557);
        addObjectTo_ObjectsInInventory(game, 561);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 101){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 558);
        removeObjectFrom_ObjectsInInventory(game, 557);
        addObjectTo_ObjectsInInventory(game, 561);
        game->idOfObjectMountedOnMouse = 0;
      }
	}


	if(EventId == 102){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 560);
        removeObjectFrom_ObjectsInInventory(game, 561);
        addObjectTo_ObjectsInInventory(game, 562);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 103){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 560);
        removeObjectFrom_ObjectsInInventory(game, 561);
        addObjectTo_ObjectsInInventory(game, 562);
        game->idOfObjectMountedOnMouse = 0;
      }
	}


	if(EventId == 104){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 562);
        removeObjectFrom_ObjectsInInventory(game, 572);
        addObjectTo_ObjectsInInventory(game, 563);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 107){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 562);
        removeObjectFrom_ObjectsInInventory(game, 572);
        addObjectTo_ObjectsInInventory(game, 563);
        game->idOfObjectMountedOnMouse = 0;
      }
	}

	if(EventId == 105){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 568);
        removeObjectFrom_ObjectsInInventory(game, 569);
        addObjectTo_ObjectsInInventory(game, 573);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 106){
      if(clickCount == 0){
        letEmSpeak(game, 69);
        removeObjectFrom_ObjectsInInventory(game, 568);
        removeObjectFrom_ObjectsInInventory(game, 569);
        addObjectTo_ObjectsInInventory(game, 573);
        game->idOfObjectMountedOnMouse = 0;
      }
	}

}

void handleEventId_3(GameState *game, int EventId, int clickCount, int objektID){
    if(EventId == 200){
      if(clickCount == 0){
        letEmSpeak(game, 13);
        removeObjectFrom_ObjectsInInventory(game, 552);
        removeFromGameDisplay(game, 0, 11);
        removeFromGameDisplay(game, 0, 300);
        removeFromGameDisplay(game, 0, 301);
        changeClickCountOfObject(game, 307, 1);
        game->idOfObjectMountedOnMouse = 0;

      }
	}
	if(EventId == 201){
      if(clickCount == 0){
        removeFromGameDisplay(game, 0, 303);
        removeObjectFrom_ObjectsInInventory(game, 556);
        addObjectTo_Array(game, 0, 2, 304);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 202){
      if(clickCount == 0){
        removeFromGameDisplay(game, 0, 304);
        removeObjectFrom_ObjectsInInventory(game, 554);
        addObjectTo_Array(game, 0, 2, 305);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 203){
      if(clickCount == 0){
        removeFromGameDisplay(game, 0, 305);
        removeObjectFrom_ObjectsInInventory(game, 559);
        addObjectTo_Array(game, 0, 2, 306);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 204){
      if(clickCount == 0){
        letEmSpeak(game, 53);
        removeObjectFrom_ObjectsInInventory(game, 555);
        addObjectTo_ObjectsInInventory(game, 565);
        removeFromGameDisplay(game, 0, 306);
        game->idOfObjectMountedOnMouse = 0;

      }
	}
	if(EventId == 205){
      if(clickCount == 0){
        letEmSpeak(game, 18);
        removeObjectFrom_ObjectsInInventory(game, 553);
        addObjectTo_Array(game, 0, 2, 321);
        changeClickCountOfObject(game, objektID, 5);
        game->idOfObjectMountedOnMouse = 0;

      }
	}
	if(EventId == 206){
      if(clickCount == 0){
        letEmSpeak(game, 28);
        addObjectTo_ObjectsInInventory(game, 556);
        game->idOfObjectMountedOnMouse = 0;
        changeInteraction_CRAFT_EventCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 29);
        addObjectTo_ObjectsInInventory(game, 557);
        game->idOfObjectMountedOnMouse = 0;
        changeInteraction_CRAFT_EventCountOfObject(game, objektID, 2);
      } else if(clickCount == 2){
        letEmSpeak(game, 30);
        addObjectTo_ObjectsInInventory(game, 566);
        game->idOfObjectMountedOnMouse = 0;
        changeInteraction_CRAFT_EventCountOfObject(game, objektID, 3);
      } else if(clickCount == 3){
        letEmSpeak(game, 31);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 208){
      if(clickCount == 0){
        letEmSpeak(game, 60);
        removeObjectFrom_ObjectsInInventory(game, 563);
        addObjectTo_ObjectsInInventory(game, 564);
        changeClickCountOfObject(game, 307, 10);
        changeClickCountOfObject(game, 310, 10);
        changeClickCountOfObject(game, 324, 10);
      }
	}
	if(EventId == 209){
      if(clickCount == 0){
        Blackscreen(game, 3000, false, 0);
        game->collectibleObjects[17].xPosition = 750;
        game->collectibleObjects[17].yPosition = 200;
        game->collectibleObjects[17].EventId = 54;
        game->collectibleObjects[17].OnlyUsableWhenNear = false;
        addObjectTo_Array(game, 4, 4, 567);
        removeObjectFrom_ObjectsInInventory(game, 567);
      }
	}
	if(EventId == 210){
      if(clickCount == 0){
        letEmSpeak(game, 101);
        removeObjectFrom_ObjectsInInventory(game, 571);
        changeClickCountOfObject(game, objektID, 3);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 211){
      if(clickCount == 0){
//        playSound(game, 138, 1); //cat
        letEmSpeak(game, 101);
        removeObjectFrom_ObjectsInInventory(game, 573);
        addObjectTo_ObjectsInInventory(game, 571);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 212){
      if(clickCount == 0){
        letEmSpeak(game, 98);
        addObjectTo_ObjectsInInventory(game, 569);
        game->idOfObjectMountedOnMouse = 0;
        changeClickCountOfObject(game, objektID, 1);
      }
	}
    if(EventId == 213){
      if(clickCount == 0){
        letEmSpeak(game, 6);
        addObjectTo_ObjectsInInventory(game, 551);
        removeFromGameDisplay(game, 0, 319);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
     if(EventId == 214){
      if(clickCount == 0){
        letEmSpeak(game, 8);
        addObjectTo_ObjectsInInventory(game, 552);
        removeFromGameDisplay(game, 0, 320);
        game->idOfObjectMountedOnMouse = 0;

      }
	}
	if(EventId == 216){
      if(clickCount == 0){
        letEmSpeak(game, 61);
        addObjectTo_ObjectsInInventory(game, 572);
        removeObjectFrom_ObjectsInInventory(game, 550);
        game->idOfObjectMountedOnMouse = 0;

      }
	}
	if(EventId == 217){
      if(clickCount == 0){
        letEmSpeak(game, 36);
        addObjectTo_ObjectsInInventory(game, 553);
        game->idOfObjectMountedOnMouse = 0;
        changeInteraction_CRAFT_EventCountOfObject(game, objektID, 1);
      } else if(clickCount == 1){
        letEmSpeak(game, 37);
        removeObjectFrom_ObjectsInInventory(game, 566);
        game->idOfObjectMountedOnMouse = 0;
        changeInteraction_CRAFT_EventCountOfObject(game, objektID, 2);
        changeClickCountOfObject(game, objektID, 1);
      }
	}
	if(EventId == 218){
      if(clickCount == 0){
        letEmSpeak(game, 43);
        removeObjectFrom_ObjectsInInventory(game, 565);
        removeFromGameDisplay(game, 2, 325);
        addObjectTo_Array(game, 2, 2, 326);
        changeClickCountOfObject(game, 310, 1);
        game->idOfObjectMountedOnMouse = 0;
      }
	}
	if(EventId == 219){
      if(clickCount == 0){
        letEmSpeak(game, 44);
        removeObjectFrom_ObjectsInInventory(game, 564);
        game->idOfObjectMountedOnMouse = 0;
      //  playSound(game, 137, 1); //explosion
        game->currentRoom = 3;
        Blackscreen(game, 3000, false, 0);
        game->person.x = 150;
        game->person.y = 300;
        letEmSpeak(game, 80);
      }
	}
}

void* handleEventId(void* parameter){
    //passToThreadStruct_Event *p = parameter;
    GameState *game = GAME;
    int EventId = EVENTID;
    int clickCount = CLICKCOUNT;
    int objektID = OBJEKTID;
     pthread_t thread_handle = PTHREAD_HANDLE;
//    pthread_t thread_handle = p->thread_handle;

    pthread_detach(thread_handle);

    printf("Eventid: %d , clickCount: %d\n", EventId, clickCount);

	if(EventId < 100){handleEventId_1(game, EventId, clickCount, objektID);}
	if(EventId < 200 && EventId >= 100){handleEventId_2(game, EventId, clickCount, objektID);}
	if(EventId <= 300 && EventId >= 200){handleEventId_3(game, EventId, clickCount, objektID);}


    return 0;
}

void startEvent(GameState *game, int eventID, int clickCount, int objectID){
    pthread_t thread_handle;

    //printf("Eventid: %d , clickCount: %d\n", eventID, clickCount);
    //game->currentRoom = 1;

    GAME = game;
    EVENTID = eventID;
    CLICKCOUNT = clickCount;
    OBJEKTID = objectID;
    PTHREAD_HANDLE = thread_handle;
//    passToThreadStruct_Event eventParameters = {game, thread_handle};

    int ret = pthread_create(&thread_handle, 0, handleEventId, &game);

    if( ret != 0){
        printf("Create thread failed! Error= %d", ret);

    }
    pthread_detach(thread_handle);
}
