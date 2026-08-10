#include "global.h"
#include "story_mode.h"
#include "constants/dungeon.h"

static EWRAM_INIT bool8 sStoryModeSkipDungeons = TRUE;

void StoryMode_ResetRuntimeState(void)
{
    sStoryModeSkipDungeons = TRUE;
}

bool8 StoryMode_IsDungeonSkipEnabled(void)
{
    return sStoryModeSkipDungeons;
}

void StoryMode_ToggleDungeonSkip(void)
{
    sStoryModeSkipDungeons = !sStoryModeSkipDungeons;
}

bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr)
{
    if (!sStoryModeSkipDungeons)
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
