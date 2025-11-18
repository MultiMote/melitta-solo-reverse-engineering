#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"
#include "buttons.h"
#include "potentiometer.h"

int main()
{
    leds_init();
    buttons_init();
    pot_init();

    uint8_t idx = 0;
    uint8_t last_idx = 0;

    set_led_by_index(idx, 1);

    while (1)
    {
        _delay_ms(10);

        idx = pot_read() * 10 / 1024;

        if (last_idx != idx)
        {
            set_led_by_index(last_idx, 0);
            set_led_by_index(idx, 1);
            last_idx = idx;
        }
    }
}
