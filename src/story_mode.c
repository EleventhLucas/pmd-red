#include "global.h"
#include "code_80958E8.h"
#include "story_mode.h"
#include "constants/dungeon.h"
#include "constants/item.h"

static EWRAM_INIT bool8 sStoryModeSkipDungeons = TRUE;

static void CompleteTakenJobsInDungeon(u8 dungeonId)
{
    s32 i;

    for (i = 0; i < MAX_ACCEPTED_JOBS; i++) {
        WonderMail *job = GetJobSlotInfo(i);

        if (job->mailType == MAIL_TYPE_TAKEN_JOB
            && job->dungeonSeed.location.id == dungeonId) {
            job->mailType = MAIL_TYPE_UNK9;
        }
    }
}

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

bool8 StoryMode_ShouldBypassItemCheck(u8 itemId)
{
    return sStoryModeSkipDungeons && itemId == ITEM_CHESTNUT;
}

bool8 StoryMode_ShouldSkipDungeon(const DungeonSetupStruct *setupPtr)
{
    if (!sStoryModeSkipDungeons)
        return FALSE;

    // Friend rescues use their own mail and reward flow and must be played normally.
    if (setupPtr->info.sub0.missionKind == DUNGEON_MISSION_OUTONRESCUE)
        return FALSE;

    if (setupPtr->info.sub0.unk4)
        return FALSE;

    return TRUE;
}

void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr)
{
    CompleteTakenJobsInDungeon(setupPtr->info.sub0.unk0.id);

    setupPtr->info.unk7C = 1;
    setupPtr->info.unk7E = 0;
    setupPtr->info.unk80 = setupPtr->info.sub0.unk0;
}
