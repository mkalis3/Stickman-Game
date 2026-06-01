# QA

## Automated Checks

`scripts/check_project.py` validates the public repository shape:

- required source, include, docs, and test files exist
- build output folders are not committed
- runtime source files stay below agreed line limits
- core source files do not contain commented-out code or suspicious portfolio text
- MPLAB project metadata references the split source files

The host-side C test suite compiles and runs `src/game_state.c` with `gcc` in GitHub Actions.

## Test Coverage

`tests/test_game_state.c` covers:

- reset state and difficulty intervals
- horizontal wraparound on the LCD
- vertical bounds across the two LCD rows
- ball collection and deterministic respawn
- win event after the target score
- chaser timing and loss detection
- grid rendering of player, ball, and chaser cells

## Manual Board Smoke Test

1. Build with MPLAB/XC32 for PIC32MX370F512L.
2. Flash the board.
3. Confirm the LCD shows the start menu.
4. Press `1` and confirm the game starts.
5. Move with keypad `4`, `6`, `8`, and `2`.
6. Confirm horizontal wraparound at the LCD edges.
7. Toggle the difficulty switch and confirm the chaser cadence changes.
8. Collect three balls and confirm the win message and tune.
9. Let the chaser catch the player and confirm the game-over message and tune.
10. Use restart/menu switches and confirm state resets cleanly.
