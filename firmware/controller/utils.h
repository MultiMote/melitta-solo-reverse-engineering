#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <avr/io.h>

typedef struct
{
    volatile uint8_t *out_reg;
    volatile uint8_t *in_reg;
    volatile uint8_t *dir_reg;
    uint8_t pin_mask;
} io_def_t;

#define IO_BUILD(suffix, pin_n) \
    {                                 \
        .out_reg = &PORT##suffix,     \
        .dir_reg = &DDR##suffix,      \
        .in_reg = &PIN##suffix,       \
        .pin_mask = _BV((pin_n))      \
    }

#define pin_on(port,pin_mask) do { (port) |= (pin_mask); } while (0);
#define pin_off(port,pin_mask) do { (port) &= ~(pin_mask); } while (0);
#define pin_set(port,pin_mask,on) do { if (on) { pin_on((port),(pin_mask)); } else { pin_off((port),(pin_mask)); } } while (0);
#define pin_check(port,pin_mask) (((port) & (pin_mask)) != 0)

#define configure_input(iodef) (*(iodef).dir_reg &= ~((iodef).pin_mask))
#define configure_output(iodef) (*(iodef).dir_reg |= ((iodef).pin_mask))
#define io_check(iodef) pin_check(*(iodef).in_reg, (iodef).pin_mask)
#define io_on(iodef) pin_on(*(iodef).out_reg, (iodef).pin_mask)
#define io_off(iodef) pin_off(*(iodef).out_reg, (iodef).pin_mask)

#endif // UTILS_H_
