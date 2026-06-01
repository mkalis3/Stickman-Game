#include <xc.h>

#include "../include/audio.h"
#include "../include/board_config.h"
#include "../include/board_init.h"
#include "../include/lcd_driver.h"

void Board_Init(void)
{
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC4 = 0;
    TRISGbits.TRISG6 = 0;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;

    TRISCbits.TRISC3 = 1;
    TRISGbits.TRISG7 = 1;
    TRISGbits.TRISG8 = 1;
    TRISGbits.TRISG9 = 1;
    ANSELGbits.ANSG7 = 0;
    ANSELGbits.ANSG8 = 0;
    ANSELGbits.ANSG9 = 0;
    CNPUCbits.CNPUC3 = 1;
    CNPUGbits.CNPUG7 = 1;
    CNPUGbits.CNPUG8 = 1;
    CNPUGbits.CNPUG9 = 1;

    Audio_Init();
    LCD_Init();

    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    LATA = 0;

    TRISFbits.TRISF3 = 1;
    TRISFbits.TRISF5 = 1;
    TRISFbits.TRISF4 = 1;
    TRISDbits.TRISD15 = 1;

    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
}
