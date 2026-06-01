#include "../include/display_assets.h"
#include "../include/lcd_driver.h"

static const char stickmanFrame[8] = {
    0b00000,
    0b00100,
    0b01110,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b00000
};

static const char ballFrame[8] = {
    0b00000,
    0b00110,
    0b01111,
    0b01111,
    0b01111,
    0b00110,
    0b00000,
    0b00000
};

static const char chaserFrame[8] = {
    0b00000,
    0b11011,
    0b11111,
    0b10101,
    0b11111,
    0b11011,
    0b00000,
    0b00000
};

void DisplayAssets_Load(void)
{
    LCD_LoadCustomChar(0, stickmanFrame);
    LCD_LoadCustomChar(1, ballFrame);
    LCD_LoadCustomChar(2, chaserFrame);
}
