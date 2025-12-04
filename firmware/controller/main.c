#include <avr/io.h>
#include <util/delay.h>
#include "periph.h"

int main()
{
    hw_init();

    _delay_ms(500);
    be_motor_parking_on_startup();

    _delay_ms(2500);
    be_motor_press();

    _delay_ms(2500);
    be_motor_unpress();

    _delay_ms(2500);

    be_motor_parking_after_brew();

    while (1)
    {
        _delay_ms(500);
    }
}
