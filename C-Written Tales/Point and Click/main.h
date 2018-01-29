#ifndef MAIN_H
#define MAIN_H

extern int done;

extern int checkIfMoveAllowed(GameState *game, int x, int y, int widthOfObject, int heightOfObject, int xMove, int yMove);

extern int shutDownGame(GameState *game, SDL_Window *window, SDL_Renderer *renderer);
extern int loadGame(GameState *game);
extern int processEvents(SDL_Window *window, GameState *game);

#endif
