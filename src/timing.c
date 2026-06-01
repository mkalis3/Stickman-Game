#include <xc.h>

#include "../include/board_config.h"
#include "../include/timing.h"

void Delay_us(unsigned int us)
{
    unsigned int start = _CP0_GET_COUNT();
    unsigned int wait = (SYS_FREQ / 2U / 1000000U) * us;
    while ((_CP0_GET_COUNT() - start) < wait) {
    }
}

void Delay_ms(unsigned int ms)
{
    while (ms-- > 0U) {
        Delay_us(1000U);
    }
}
