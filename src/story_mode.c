#include "global.h"
#include "story_mode.h"
#include "constants/dungeon.h"

#define STORY_MODE_SKIP_DUNGEONS 1

bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr)
{
    if (!STORY_MODE_SKIP_DUNGEONS)
        return FALSE;

    if (setupPtr->info.sub0.unk4)
        return FALSE;

    return TRUE;
}

void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr)
{
    if (setupPtr->info.sub0.missionKind == DUNGEON_MISSION_OUTONRESCUE) {
        setupPtr->info.unk7C = 4;
    }
    else {
        setupPtr->info.unk7C = 1;
    }

    setupPtr->info.unk7E = 0;
    setupPtr->info.unk80 = setupPtr->info.sub0.unk0;
}
