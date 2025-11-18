#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"

int main()
{
    leds_init();

    while (1)
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            set_led_by_index(i, 1);
            _delay_ms(200);
        }

        for (uint8_t i = 0; i < 10; i++)
        {
            set_led_by_index(i, 0);
            _delay_ms(200);
        }
    }
}
