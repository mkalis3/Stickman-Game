#include <xc.h>

#include "../include/board_config.h"
#include "../include/keypad.h"
#include "../include/timing.h"

static char keypad[4][4] = {
    {'D', 'C', 'B', 'A'},
    {'E', '9', '6', '3'},
    {'F', '8', '5', '2'},
    {'0', '7', '4', '1'}
};

static int CheckCols(int row)
{
    if (!COL1) {
        return (row << 4) | 0;
    }
    if (!COL2) {
        return (row << 4) | 1;
    }
    if (!COL3) {
        return (row << 4) | 2;
    }
    if (!COL4) {
        return (row << 4) | 3;
    }

    return -1;
}

char Keypad_Scan(void)
{
    for (int row = 0; row < 4; row++) {
        ROW1 = 1;
        ROW2 = 1;
        ROW3 = 1;
        ROW4 = 1;

        switch (row) {
            case 0:
                ROW1 = 0;
                break;
            case 1:
                ROW2 = 0;
                break;
            case 2:
                ROW3 = 0;
                break;
            default:
                ROW4 = 0;
                break;
        }

        Delay_us(200U);
        int col = CheckCols(row);
        if (col >= 0) {
            Delay_ms(50U);
            if (CheckCols(row) == col) {
                int stableRow = col >> 4;
                int stableCol = col & 0x0F;
                return keypad[stableRow][stableCol];
            }
        }
    }

    return 0;
}
