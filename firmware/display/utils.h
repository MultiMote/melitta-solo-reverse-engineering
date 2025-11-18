#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

inline void pin_on(volatile uint8_t *port, uint8_t pin_mask)
{
    *port |= pin_mask;
}

inline void pin_off(volatile uint8_t *port, uint8_t pin_mask)
{
    *port &= ~pin_mask;
}

inline void pin_set(volatile uint8_t *port, uint8_t pin_mask, uint8_t on)
{
    if (on)
    {
        pin_on(port, pin_mask);
    }
    else
    {
        pin_off(port, pin_mask);
    }
}

inline uint8_t pin_check(const volatile uint8_t *port, uint8_t pin_mask)
{
    return (*port & pin_mask) != 0;
}

#endif // UTILS_H_
