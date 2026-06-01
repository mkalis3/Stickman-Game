#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char row, unsigned char col);
void LCD_String(const char *text);
void LCD_Data(unsigned char data);
void LCD_LoadCustomChar(unsigned char location, const char *pattern);

#endif
