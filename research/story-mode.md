# Story Mode Notes

Story mode keeps the ground/hub systems and friend areas intact while avoiding
the dungeon exploration loop.

## First Patch

The current prototype hooks `LoadAndRunDungeon_Async` in `src/main_loops.c`.
Before it calls `RunDungeon_Async`, it asks `story_mode.c` whether the dungeon
should be skipped.

Story mode uses a runtime-only EWRAM flag. It defaults to on at boot and is
reset to on when saved options are initialized or read, but it is not serialized
to the save file. Emulator save states preserve it naturally because they
preserve RAM.

The "Others" menu has a non-saved `Story: On` / `Story: Off` entry. Toggling it
immediately flips whether dungeon runs are skipped.

When skipping is enabled, `StoryMode_CompleteSkippedDungeon` writes the same
high-level result shape the main loop already handles after a successful dungeon:

- `unk7C = 1` for normal dungeon wins.
- `unk7C = 4` for out-on-rescue wins.
- `unk7E = 0`, so `EVENT_S08E01[0]` becomes `1`.
- `unk80` is set to the requested dungeon location.

This lets the existing `STARTMODE_DUNGEON_WON` ground-script path run without
entering the dungeon engine.

## Intentional Limits

- The dungeon engine is still compiled and linkable.
- Quicksave dungeon resumes are not skipped.
- Normal in-game saves do not preserve the toggle state; it intentionally resets
  to on after load.
- Optional mission completion side effects are not fully simulated yet.
- Dungeon-specific boss/cutscene transitions still need case-by-case mapping.

## Next Targets

- Make the skip policy data-driven by script dungeon or rescue dungeon ID.
- Map early story dungeons and confirm their post-clear ground scripts.
- Add special result handling for boss/story dungeons that rely on cutscene flags
  or nonstandard dungeon exit reasons.
