#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include <avr/io.h>

void pot_init()
{
    // AVCC reference, ADC7 channel
    ADMUX = _BV(REFS0) | 7;

    // Enable ADC, set prescaler to 64 (8MHz / 64 = 125kHz)
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
}

uint16_t pot_read()
{
    // Start conversion
    ADCSRA |= _BV(ADSC);
    // Wait for conversion complete
    while (ADCSRA & _BV(ADSC))
    {
    }
    // Return 0-1024
    return ADC;
}

#endif // POTENTIOMETER_H_
