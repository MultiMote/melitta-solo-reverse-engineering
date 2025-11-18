#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>
#include <util/delay.h>

#include "utils.h"

#define BUTTON_1_PIN PINC4
#define BUTTON_2_PIN PINC5
#define BUTTON_3_PIN PIND0
#define HALL_PIN PIND1
#define BUTTON_JITTER_MS 30

enum button_index
{
    BUTTON_CUP = 0,
    BUTTON_BEAN,
    BUTTON_STEAM,
    BUTTON_HALL,
};

static inline uint8_t is_button_pressed(enum button_index index)
{
    switch (index)
    {
    case BUTTON_CUP:
        return !pin_check(&PINC, _BV(BUTTON_1_PIN));
    case BUTTON_BEAN:
        return !pin_check(&PINC, _BV(BUTTON_2_PIN));
    case BUTTON_STEAM:
        return !pin_check(&PIND, _BV(BUTTON_3_PIN));
    case BUTTON_HALL:
        return !pin_check(&PIND, _BV(HALL_PIN));
    }
    return 0;
}

static inline void wait_button_release(enum button_index index)
{
    do
    {
        _delay_ms(BUTTON_JITTER_MS);
    } while (is_button_pressed(index));
}

static inline void buttons_init()
{
    DDRD &= ~(_BV(HALL_PIN) | _BV(BUTTON_3_PIN));
    DDRC &= ~(_BV(BUTTON_1_PIN) | _BV(BUTTON_2_PIN));
}

#endif // BUTTONS_H_
