#include <stdint.h>
#include <xc.h>

#include "../include/board_config.h"
#include "../include/lcd_driver.h"
#include "../include/timing.h"

static void LCD_Command(uint8_t command)
{
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DATA = command;
    LCD_EN = 1;
    Delay_us(50U);
    LCD_EN = 0;
    Delay_ms(2U);
}

void LCD_Data(unsigned char data)
{
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DATA = data;
    LCD_EN = 1;
    Delay_us(50U);
    LCD_EN = 0;
    Delay_us(50U);
}

void LCD_Init(void)
{
    LCD_DATA_TRIS &= 0xFF00;
    LCD_RS_TRIS = 0;
    LCD_RW_TRIS = 0;
    LCD_EN_TRIS = 0;

    Delay_ms(20U);
    LCD_Command(0x38);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
    Delay_ms(2U);
}

void LCD_SetCursor(unsigned char row, unsigned char col)
{
    LCD_Command(0x80 | ((row ? 0x40 : 0x00) + col));
}

void LCD_String(const char *text)
{
    while (*text != '\0') {
        LCD_Data((unsigned char)*text++);
    }
}

void LCD_LoadCustomChar(unsigned char location, const char *pattern)
{
    LCD_Command(0x40 + (location << 3));
    for (int i = 0; i < 8; i++) {
        LCD_Data((unsigned char)pattern[i]);
    }
}
