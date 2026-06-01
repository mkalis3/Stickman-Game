#include <sys/attribs.h>
#include <xc.h>

#include "../include/audio.h"
#include "../include/board_config.h"
#include "../include/timing.h"

const unsigned int WIN_NOTES[] = {523, 659, 784, 1046};
const unsigned int WIN_DURS[] = {300, 300, 300, 600};
const int WIN_LEN = 4;

const unsigned int LOSE_NOTES[] = {392, 330, 262};
const unsigned int LOSE_DURS[] = {300, 300, 600};
const int LOSE_LEN = 3;

static const unsigned int MOVE_NOTES[] = {440};
static const unsigned int MOVE_DURS[] = {50};
static const int MOVE_LEN = 1;

static const unsigned int COLLECT_NOTES[] = {523};
static const unsigned int COLLECT_DURS[] = {100};
static const int COLLECT_LEN = 1;

#define MENU_LEN 4
static const unsigned int MENU_NOTES[MENU_LEN] = {262, 294, 330, 349};
static const unsigned int MENU_DURS[MENU_LEN] = {500, 500, 500, 500};

static volatile int soundEnabled = 0;
static int menuMelodyIndex = 0;
static int menuMelodyTime = 0;
static int isMenuPlaying = 0;

void __ISR(_TIMER_3_VECTOR, IPL5SOFT) T3InterruptHandler(void)
{
    OC1RS = soundEnabled ? (PR3 / 2U) : 0U;
    IFS0bits.T3IF = 0;
}

static void Audio_SetFrequency(unsigned int frequency)
{
    if (frequency < 50U) {
        frequency = 50U;
    }

    T3CONbits.ON = 0;
    TMR3 = 0;
    unsigned int period = (SYS_FREQ / (frequency * 2U)) - 1U;

    if (period > 65535U) {
        T3CONbits.TCKPS = 3;
        period = ((SYS_FREQ / 8U) / (frequency * 2U)) - 1U;
        if (period > 65535U) {
            period = 65535U;
        }
    } else {
        T3CONbits.TCKPS = 0;
    }

    PR3 = period;
    T3CONbits.ON = 1;
}

void Audio_Init(void)
{
    TRISBbits.TRISB14 = 0;
    ANSELBbits.ANSB14 = 0;
    RPB14R = 0x0C;
    T3CON = 0;
    TMR3 = 0;
    PR3 = 5000;
    T3CONbits.TCKPS = 0;
    T3CONbits.ON = 1;
    OC1CON = 0;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.ON = 1;
    IPC3bits.T3IP = 5;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
}

void Audio_PlayMelody(const unsigned int *notes, const unsigned int *durations, int length)
{
    for (int i = 0; i < length; i++) {
        Audio_SetFrequency(notes[i]);
        soundEnabled = 1;
        Delay_ms(durations[i]);
        soundEnabled = 0;
        Delay_ms(50U);
    }
}

void Audio_PlayMove(void)
{
    Audio_PlayMelody(MOVE_NOTES, MOVE_DURS, MOVE_LEN);
}

void Audio_PlayCollect(void)
{
    Audio_PlayMelody(COLLECT_NOTES, COLLECT_DURS, COLLECT_LEN);
}

void Audio_StartMenuMelody(void)
{
    isMenuPlaying = 1;
    menuMelodyIndex = -1;
    menuMelodyTime = 0;
}

void Audio_StopMenuMelody(void)
{
    isMenuPlaying = 0;
    soundEnabled = 0;
    menuMelodyIndex = 0;
    menuMelodyTime = 0;
}

void Audio_UpdateMenuMelody(unsigned int elapsed_ms)
{
    if (!isMenuPlaying) {
        Audio_StartMenuMelody();
    }

    if (menuMelodyTime <= 0) {
        menuMelodyIndex++;
        if (menuMelodyIndex >= MENU_LEN) {
            menuMelodyIndex = 0;
        }

        Audio_SetFrequency(MENU_NOTES[menuMelodyIndex]);
        soundEnabled = 1;
        menuMelodyTime = MENU_DURS[menuMelodyIndex];
        return;
    }

    menuMelodyTime -= (int)elapsed_ms;
}
