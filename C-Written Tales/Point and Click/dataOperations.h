#ifndef DATAOPERATIONS_H
#define DATAOPERATIONS_H



//Game Logic - Render - Load
extern int loadImagesInMemory(GameState *game);

extern int loadAudioInMemory(GameState *game);


extern void fillRenderedObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID);

extern void fillInteractiveRenderedObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID,
                                     bool clickable, int clickCount, int EventID, bool interactiveWithObject, int idOfNeededObjectToInteract, bool OnlyUsableWhenNear,
                                     int InteractionEventID, int InteractionEventCount);

extern void fillCollectibleObjects(GameState *game, int index, int id, int xPosition, int yPosition, int width, int height, int imgID,
                            bool clickable, int clickCount, int EventID, bool ableToCraft, int idOfNeededObjectToCraft, bool OnlyUsableWhenNear,
                            int CraftEventID, int CraftEventCount);


//Data Logic - runtimeArrays
extern void initRuntimeArrays(GameState *game);

extern void addObjectTo_ObjectsInInventory(GameState *game, int idToAdd);

extern void removeObjectFrom_ObjectsInInventory(GameState *game, int idToDelete);


extern void addObjectTo_Array(GameState *game, int roomToAddTo, int ArrayToAdd, int idToAdd);

extern void removeObjectFrom_Array(GameState *game, int roomToDeleteFrom, int ArrayToChange, int idToDelete);

extern void addObjectTo_OneTimeAnimations(GameState *game, int idToAdd_Object, int AnimationId);

extern void removeObjectFrom_OneTimeAnimations(GameState *game, int idToDelete);

extern void addObjectTo_LoopAnimations(GameState *game, int idToAdd_Object, int AnimationId);

extern void removeObjectFrom_LoopAnimations(GameState *game, int idToDelete);

extern void removeFromGameDisplay(GameState *game, int roomToDeleteFrom, int idToRemove);

extern void clearGameDisplay(GameState *game, int roomToClear);


#endif

