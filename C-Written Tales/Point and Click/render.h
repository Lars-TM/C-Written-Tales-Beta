#ifndef RENDER_H
#define RENDER_H

extern void updateCurrentlyOnDisplay(GameState *game, int xPosition, int yPosition, int widht, int height, int idToUpdate);

extern void updateAllowedToWalkHere(GameState *game, int xPosition, int yPosition, int width, int height, int idToUpdate);

extern void drawImage(GameState *game, SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int width, int height);

extern void drawRectangle(GameState *game, SDL_Renderer *renderer, int x, int y, int width, int height);

extern void drawLayer(GameState *game, int LayerToDraw, int roomToDraw);

extern void drawInventory(GameState *game);

extern void animateCharackter(GameState *game, int direction);

extern void loopAnimateObjects(GameState *game);

extern void OneTimeAnimateObjects(GameState *game);


extern void doRender(SDL_Renderer *renderer, GameState *game);


#endif

