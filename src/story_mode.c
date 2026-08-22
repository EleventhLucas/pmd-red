#include "global.h"
#include "code_80958E8.h"
#include "story_mode.h"
#include "constants/cutscenes.h"
#include "constants/dungeon.h"
#include "constants/item.h"

static EWRAM_INIT bool8 sStoryModeSkipDungeons = TRUE;
static EWRAM_INIT bool8 sStoryModeSceneDungeonActive = FALSE;

static bool8 GetSceneDungeonLocation(u8 dungeonId, DungeonLocation *location)
{
    location->id = dungeonId;

    switch (dungeonId) {
        case DUNGEON_MT_STEEL:
            location->floor = 9;
            return TRUE;
        case DUNGEON_SINISTER_WOODS:
            location->floor = 13;
            return TRUE;
        case DUNGEON_MT_THUNDER_PEAK:
            location->floor = 3;
            return TRUE;
        case DUNGEON_MT_BLAZE_PEAK:
            location->floor = 3;
            return TRUE;
        case DUNGEON_FROSTY_GROTTO:
            location->floor = 5;
            return TRUE;
        case DUNGEON_MT_FREEZE_PEAK:
            location->floor = 5;
            return TRUE;
        case DUNGEON_MAGMA_CAVERN_PIT:
            location->floor = 2;
            return TRUE;
        case DUNGEON_SKY_TOWER_SUMMIT:
            location->floor = 9;
            return TRUE;
        case DUNGEON_UPROAR_FOREST:
            location->floor = 10;
            return TRUE;
        case DUNGEON_HOWLING_FOREST:
            location->floor = 15;
            return TRUE;
    }

    return FALSE;
}

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
    sStoryModeSceneDungeonActive = FALSE;
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

bool8 StoryMode_PrepareSceneDungeon(DungeonSetupStruct *setupPtr)
{
    DungeonLocation location;

    sStoryModeSceneDungeonActive = FALSE;

    if (!sStoryModeSkipDungeons)
        return FALSE;

    if (setupPtr->info.sub0.missionKind == DUNGEON_MISSION_OUTONRESCUE)
        return FALSE;

    if (setupPtr->info.sub0.unk4)
        return FALSE;

    if (GetSceneDungeonLocation(setupPtr->info.sub0.unk0.id, &location)) {
        CompleteTakenJobsInDungeon(setupPtr->info.sub0.unk0.id);
        setupPtr->info.sub0.unk0 = location;
        sStoryModeSceneDungeonActive = TRUE;
        return TRUE;
    }

    return FALSE;
}

bool8 StoryMode_ShouldSuppressDungeonTutorials(void)
{
    return sStoryModeSceneDungeonActive;
}

bool8 StoryMode_ShouldAutoAdvanceSceneFloor(u8 dungeonId, u8 cutscene)
{
    DungeonLocation location;

    if (!sStoryModeSceneDungeonActive)
        return FALSE;

    if (!GetSceneDungeonLocation(dungeonId, &location))
        return FALSE;

    if (cutscene == CUTSCENE_NONE || cutscene == NUM_CUTSCENES)
        return FALSE;

    return TRUE;
}

void StoryMode_CompleteSkippedDungeon(DungeonSetupStruct *setupPtr)
{
    sStoryModeSceneDungeonActive = FALSE;

    CompleteTakenJobsInDungeon(setupPtr->info.sub0.unk0.id);

    setupPtr->info.unk7C = 1;
    setupPtr->info.unk7E = 0;
    setupPtr->info.unk80 = setupPtr->info.sub0.unk0;
}
