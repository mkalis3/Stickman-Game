#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "audio.h"
#include "board_config.h"
#include "board_init.h"
#include "display_assets.h"
#include "game_state.h"
#include "keypad.h"
#include "lcd_driver.h"
#include "timing.h"

#pragma config JTAGEN   = OFF
#pragma config FWDTEN   = OFF
#pragma config FNOSC    = FRCPLL
#pragma config FSOSCEN  = OFF
#pragma config POSCMOD  = EC
#pragma config OSCIOFNC = ON
#pragma config FPBDIV   = DIV_1
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL  = MUL_20
#pragma config FPLLODIV = DIV_1

static GameState game;
static char grid[GAME_ROWS][GAME_COLS];

static void ShowMainMenu(void);
static void InitGame(void);

static unsigned int RandomBounded(unsigned int upperBound)
{
    if (upperBound == 0U) {
        return 0U;
    }

    return (unsigned int)(rand() % upperBound);
}

static GameDifficulty ReadDifficulty(void)
{
    return SW1 == 1 ? GAME_DIFFICULTY_HARD : GAME_DIFFICULTY_NORMAL;
}

static void RenderGame(void)
{
    game_state_render(&game, grid);
    LCD_Clear();

    for (int row = 0; row < GAME_ROWS; row++) {
        LCD_SetCursor((unsigned char)row, 0);
        for (int col = 0; col < GAME_COLS; col++) {
            LCD_Data((unsigned char)grid[row][col]);
        }
    }
}

static void EndGameMessage(const char *line1, const char *line2, const unsigned int *notes, const unsigned int *durations, int length)
{
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_String(line1);
    LCD_SetCursor(1, 0);
    LCD_String(line2);

    Audio_PlayMelody(notes, durations, length);
    Delay_ms(5000U);
    InitGame();
    ShowMainMenu();
}

static void HandleGameResult(GameResult result)
{
    if ((result.events & GAME_EVENT_PLAYER_MOVED) != 0) {
        Audio_PlayMove();
    }

    if ((result.events & GAME_EVENT_WON) != 0) {
        char message[16];
        sprintf(message, "Score: %d", result.score);
        EndGameMessage("YOU WIN!", message, WIN_NOTES, WIN_DURS, WIN_LEN);
        return;
    }

    if ((result.events & GAME_EVENT_LOST) != 0) {
        char message[16];
        sprintf(message, "Score: %d", result.score);
        EndGameMessage("Game Over!", message, LOSE_NOTES, LOSE_DURS, LOSE_LEN);
        return;
    }

    if ((result.events & GAME_EVENT_BALL_COLLECTED) != 0) {
        Audio_PlayCollect();
    }
}

static void InitGame(void)
{
    game_state_reset(&game, ReadDifficulty());
    RenderGame();
}

static void ShowMainMenu(void)
{
    LCD_Clear();
    LCD_String("1 Start Game");
    LCD_SetCursor(1, 0);
    LCD_String("2 Exit");

    Audio_StartMenuMelody();

    while (1) {
        if (SW3 == 1) {
            Audio_UpdateMenuMelody(MAIN_LOOP_DELAY_MS);
        } else {
            Audio_StopMenuMelody();
        }

        char key = Keypad_Scan();
        if (key == '1') {
            Audio_StopMenuMelody();
            LCD_Clear();
            LCD_String("Starting...");
            Delay_ms(500U);
            return;
        }

        if (key == '2') {
            Audio_StopMenuMelody();
            LCD_Clear();
            LCD_String("Exiting...");
            while (1) {
            }
        }

        Delay_ms(MAIN_LOOP_DELAY_MS);
    }
}

int main(void)
{
    Board_Init();
    ShowMainMenu();

    LCD_Clear();
    LCD_String("Stickman Game");
    DisplayAssets_Load();
    Delay_ms(1000U);
    InitGame();

    char lastKey = 0;
    while (1) {
        if (SW0 == 0) {
            ShowMainMenu();
            InitGame();
        }

        if (SW2 == 1) {
            InitGame();
        }

        game_state_set_difficulty(&game, ReadDifficulty());

        char key = Keypad_Scan();
        if (key != 0 && key != lastKey) {
            lastKey = key;
            GameResult result = game_state_apply_input(&game, game_input_from_key(key), RandomBounded);
            if (result.events != GAME_EVENT_NONE) {
                RenderGame();
                HandleGameResult(result);
            }
        }

        if (key == 0) {
            lastKey = 0;
        }

        Delay_ms(MAIN_LOOP_DELAY_MS);
        GameResult tickResult = game_state_tick(&game, MAIN_LOOP_DELAY_MS);
        if ((tickResult.events & GAME_EVENT_CHASER_MOVED) != 0) {
            RenderGame();
            HandleGameResult(tickResult);
        }
    }
}
