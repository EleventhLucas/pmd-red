#ifndef GUARD_STORY_MODE_H
#define GUARD_STORY_MODE_H

#include "structs/str_dungeon_setup.h"

bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr);
void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr);

#endif // GUARD_STORY_MODE_H
