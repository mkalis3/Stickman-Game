#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define SYS_FREQ 40000000UL
#define MAIN_LOOP_DELAY_MS 100U

#define SW0 PORTFbits.RF3
#define SW1 PORTFbits.RF5
#define SW2 PORTFbits.RF4
#define SW3 PORTDbits.RD15

#define LCD_RS LATBbits.LATB15
#define LCD_RW LATDbits.LATD5
#define LCD_EN LATDbits.LATD4
#define LCD_RS_TRIS TRISBbits.TRISB15
#define LCD_RW_TRIS TRISDbits.TRISD5
#define LCD_EN_TRIS TRISDbits.TRISD4
#define LCD_DATA LATE
#define LCD_DATA_TRIS TRISE

#define ROW1 LATCbits.LATC2
#define ROW2 LATCbits.LATC1
#define ROW3 LATCbits.LATC4
#define ROW4 LATGbits.LATG6
#define COL1 PORTCbits.RC3
#define COL2 PORTGbits.RG7
#define COL3 PORTGbits.RG8
#define COL4 PORTGbits.RG9

#endif
