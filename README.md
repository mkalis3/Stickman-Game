# Stickman Game

Stickman Game is an embedded C arcade game for a PIC32 board with a 16x2 LCD, matrix keypad input, switch-controlled difficulty, timer-driven audio, and a small real-time chase loop.

The public repository is organized as a firmware project with a portable game-state module that can be tested on a desktop compiler. Hardware-facing code stays isolated from deterministic gameplay rules.

## Highlights

- PIC32 firmware entrypoint in `main.c`
- LCD driver, keypad scanner, audio driver, board setup, and display assets split into dedicated modules
- Portable `game_state` module for movement, scoring, collision, difficulty, chaser timing, and rendering state
- Host-side C tests for the game-state module
- GitHub Actions checks for layout, hygiene, and desktop test compilation
- MPLAB/NetBeans project files kept for the embedded build workflow

## Project Layout

```text
include/
  audio.h
  board_config.h
  board_init.h
  display_assets.h
  game_state.h
  keypad.h
  lcd_driver.h
  timing.h
src/
  audio.c
  board_init.c
  display_assets.c
  game_state.c
  keypad.c
  lcd_driver.c
  timing.c
tests/
  test_game_state.c
main.c
nbproject/
```

## Hardware Assumptions

- PIC32MX370F512L target using XC32
- LCD data lines on port E
- LCD control lines on RB15, RD5, and RD4
- Keypad rows on RC2, RC1, RC4, and RG6
- Keypad columns on RC3, RG7, RG8, and RG9
- Board switches on RF3, RF5, RF4, and RD15

## Local Checks

Repository hygiene checks:

```bash
python scripts/check_project.py
```

Host tests on a machine with `gcc`:

```bash
gcc -std=c11 -Wall -Wextra -Werror -Iinclude tests/test_game_state.c src/game_state.c -o test_game_state
./test_game_state
```

Embedded build with MPLAB/XC32:

```bash
make build
```

## Review Notes

The game-state module is intentionally independent from `xc.h`, timers, LCD registers, and keypad pins. That makes the core behavior easy to test without the board while keeping the firmware modules close to the PIC32 hardware.
