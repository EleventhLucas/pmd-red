#ifndef GUARD_STORY_MODE_H
#define GUARD_STORY_MODE_H

#include "structs/str_dungeon_setup.h"

void StoryMode_ResetRuntimeState(void);
bool8 StoryMode_IsDungeonSkipEnabled(void);
void StoryMode_ToggleDungeonSkip(void);
bool8 StoryMode_ShouldBypassItemCheck(u8 itemId);
bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr);
bool8 StoryMode_PrepareSceneDungeon(DungeonSetupStruct *setupPtr);
bool8 StoryMode_ShouldAutoAdvanceSceneFloor(u8 dungeonId, u8 cutscene);
void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr);

#endif // GUARD_STORY_MODE_H
