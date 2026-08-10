#ifndef GUARD_STORY_MODE_H
#define GUARD_STORY_MODE_H

#include "structs/str_dungeon_setup.h"

void StoryMode_ResetRuntimeState(void);
bool8 StoryMode_IsDungeonSkipEnabled(void);
void StoryMode_ToggleDungeonSkip(void);
bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr);
void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr);

#endif // GUARD_STORY_MODE_H
