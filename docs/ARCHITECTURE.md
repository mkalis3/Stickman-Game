# Architecture

The firmware is split into hardware modules and portable game logic.

## Firmware Entry

`main.c` owns the application flow:

- board initialization
- menu flow
- game reset
- input polling
- rendering orchestration
- win and loss handling

It delegates board-specific work to drivers and delegates deterministic gameplay rules to `game_state`.

## Hardware Modules

- `board_init` configures keypad pins, switches, LEDs, LCD, audio, and interrupts.
- `lcd_driver` owns LCD commands, data writes, cursor movement, text output, and custom characters.
- `keypad` scans the 4x4 matrix keypad with debounce.
- `audio` owns Timer3, OC1, short effects, win and loss tunes, and the menu melody.
- `timing` wraps CP0-based microsecond and millisecond delays.
- `display_assets` loads custom LCD characters for the player, ball, and chaser.

## Portable Game Logic

`game_state` has no dependency on PIC32 headers. It owns:

- player movement and LCD edge wrapping
- vertical row bounds
- ball collection and score progression
- win and loss event generation
- chaser movement cadence by difficulty
- grid rendering data for the LCD driver

The module returns event flags instead of playing sounds or drawing directly. That keeps hardware side effects in `main.c` and makes tests deterministic.
