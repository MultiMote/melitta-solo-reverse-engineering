#ifndef LEDS_H_
#define LEDS_H_

#include "utils.h"

#define LED1_PIN PD5
#define LED2_PIN PD4
#define LED3_PIN PD3
#define LED4_PIN PD2
#define LED5_PIN PC3
#define LED6_PIN PC2
#define LED7_PIN PC1
#define LED8_PIN PC0
#define LED9_PIN PD7
#define LED10_PIN PD6

enum led_index
{
    LED_READY = 0,
    LED_FILTER,
    LED_WATER_TANK,
    LED_DRIP_TRAY,
    LED_BEAN_1,
    LED_BEAN_2,
    LED_BEAN_3,
    LED_CLEANING,
    LED_DESCALE,
    LED_FROTH
};

inline void set_led_by_index(uint8_t index, uint8_t value)
{
    switch (index)
    {
    case 0:
        pin_set(&PORTD, _BV(LED1_PIN), value);
        break;
    case 1:
        pin_set(&PORTD, _BV(LED2_PIN), value);
        break;
    case 2:
        pin_set(&PORTD, _BV(LED3_PIN), value);
        break;
    case 3:
        pin_set(&PORTD, _BV(LED4_PIN), value);
        break;
    case 4:
        pin_set(&PORTC, _BV(LED5_PIN), value);
        break;
    case 5:
        pin_set(&PORTC, _BV(LED6_PIN), value);
        break;
    case 6:
        pin_set(&PORTC, _BV(LED7_PIN), value);
        break;
    case 7:
        pin_set(&PORTC, _BV(LED8_PIN), value);
        break;
    case 8:
        pin_set(&PORTD, _BV(LED9_PIN), value);
        break;
    case 9:
        pin_set(&PORTD, _BV(LED10_PIN), value);
        break;
    }
}

inline void leds_init()
{
    DDRD |= _BV(LED1_PIN) | _BV(LED2_PIN) | _BV(LED3_PIN) | _BV(LED4_PIN) | _BV(LED9_PIN) | _BV(LED10_PIN);
    DDRC |= _BV(LED5_PIN) | _BV(LED6_PIN) | _BV(LED7_PIN) | _BV(LED8_PIN);
}

inline void leds_on_all()
{
    PORTD |= _BV(LED1_PIN) | _BV(LED2_PIN) | _BV(LED3_PIN) | _BV(LED4_PIN) | _BV(LED9_PIN) | _BV(LED10_PIN);
    PORTC |= _BV(LED5_PIN) | _BV(LED6_PIN) | _BV(LED7_PIN) | _BV(LED8_PIN);
}

inline void leds_off_all()
{
    PORTD &= ~(_BV(LED1_PIN) | _BV(LED2_PIN) | _BV(LED3_PIN) | _BV(LED4_PIN) | _BV(LED9_PIN) | _BV(LED10_PIN));
    PORTC &= ~(_BV(LED5_PIN) | _BV(LED6_PIN) | _BV(LED7_PIN) | _BV(LED8_PIN));
}

#endif // LEDS_H_
