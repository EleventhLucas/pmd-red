# Story Mode Notes

Story mode keeps the ground/hub systems and friend areas intact while avoiding
the dungeon exploration loop.

## First Patch

The current prototype hooks `LoadAndRunDungeon_Async` in `src/main_loops.c`.
Before it calls `RunDungeon_Async`, it asks `story_mode.c` whether the dungeon
should be skipped or scene-preserved.

Story mode uses a runtime-only EWRAM flag. It defaults to on at boot and is
reset to on when saved options are initialized or read, but it is not serialized
to the save file. Emulator save states preserve it naturally because they
preserve RAM.

The "Others" menu has a non-saved `Story: On` / `Story: Off` entry. Toggling it
immediately flips whether dungeon runs are skipped.

When skipping is enabled, `StoryMode_CompleteSkippedDungeon` writes the same
high-level result shape the main loop already handles after a successful dungeon:

- `unk7C = 1` for normal dungeon wins.
- `unk7E = 0`, so `EVENT_S08E01[0]` becomes `1`.
- `unk80` is set to the requested dungeon location.

This lets the existing `STARTMODE_DUNGEON_WON` ground-script path run without
entering the dungeon engine.

Known boss and rescue-story scene dungeons use a scene-preserving path instead
of the instant skip. `StoryMode_PrepareSceneDungeon` moves the start location to
the destination floor, lets the dungeon engine show fixed-room staging and
pre-fight dialogue, then `StoryMode_ShouldAutoAdvanceSceneFloor` skips the
playable turn loop so the run advances or clears immediately afterward.

Accepted jobs in these dungeons are completed when the endpoint scene is
prepared, matching the instant skip path. This prevents scene-preserving
dungeons from leaving jobs stuck in the accepted state.

Currently preserved endpoints:

- Mt. Steel 9F.
- Sinister Woods 13F.
- Mt. Thunder Peak 3F.
- Mt. Blaze Peak 3F.
- Frosty Grotto 5F.
- Mt. Freeze Peak 5F.
- Magma Cavern Pit 2F and the following Groudon floor.
- Sky Tower Summit 9F.
- Uproar Forest 10F.
- Howling Forest 15F.

## Intentional Limits

- The dungeon engine is still compiled and linkable.
- Quicksave dungeon resumes are not skipped.
- Friend rescues use their own mail/reward flow and are not skipped.
- Normal in-game saves do not preserve the toggle state; it intentionally resets
  to on after load.
- Optional mission completion side effects are not fully simulated yet.
- Some postgame legendary fixed-room scenes still need case-by-case mapping.

## Next Targets

- Make the skip policy data-driven by script dungeon or rescue dungeon ID.
- Map early story dungeons and confirm their post-clear ground scripts.
- Expand scene preservation to postgame legendary fixed rooms.
