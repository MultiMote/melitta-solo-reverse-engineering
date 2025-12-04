#ifndef PERIPH_H_
#define PERIPH_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "utils.h"

#define UART_BAUD 9600UL

enum be_motor_dir_t
{
    BE_MOT_DIR_STOP = 0,
    BE_MOT_DIR_FWD,
    BE_MOT_DIR_REV
};

static volatile uint32_t water_counter = 0;

static const io_def_t be_motor_fwd_io  = IO_BUILD(C, 6);
static const io_def_t be_motor_rev_io  = IO_BUILD(C, 7);
static const io_def_t be_cam_top_io    = IO_BUILD(A, 5);
static const io_def_t be_cam_bottom_io = IO_BUILD(B, 0);
static const io_def_t be_cam_press_io  = IO_BUILD(A, 6);
static const io_def_t flow_io          = IO_BUILD(B, 2);

ISR(INT2_vect)
{
    water_counter++;
}

void uart_init()
{
    uint8_t ubrr = (F_CPU / (16 * UART_BAUD)) - 1;
    // Set baud rate
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)ubrr;

    // Enable transmitter
    UCSRB = _BV(TXEN);

    // Set frame format: 8 data bits, 1 stop bit
    UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);
}

void uart_print(const char *str)
{
    while (*str)
    {
        while (!(UCSRA & (1 << UDRE)));
        UDR = *str++;
    }
}


static inline void hw_init(void)
{
    configure_output(be_motor_fwd_io);
    configure_output(be_motor_rev_io);

    configure_input(be_cam_top_io);
    configure_input(be_cam_bottom_io);
    configure_input(be_cam_press_io);
    configure_input(flow_io);

    uart_init();

    // Trigger INT2 on falling edge
    MCUCSR &= ~_BV(ISC2);
    // Enable INT2 interrupt
    GICR |= _BV(INT2);
    // Enable global interrupts
    sei();

    uart_print("hw_init done\r\n");

    char buf[32];

    while (1)
    {
        _delay_ms(1000);
        uart_print("Water count: ");
        itoa(water_counter, buf, 10);
        uart_print(buf);
        uart_print("\r\n");
    }

}

static inline uint8_t is_cam_top_pressed(void)
{
    return !io_check(be_cam_top_io);
}

static inline uint8_t is_cam_bottom_pressed(void)
{
    return !io_check(be_cam_bottom_io);
}

static inline uint8_t is_press_pressed(void)
{
    return !io_check(be_cam_press_io);
}

static inline void be_motor(enum be_motor_dir_t dir)
{
    switch (dir)
    {
    case BE_MOT_DIR_FWD:
        io_on(be_motor_fwd_io);
        io_off(be_motor_rev_io);
        break;
    case BE_MOT_DIR_REV:
        io_on(be_motor_rev_io);
        io_off(be_motor_fwd_io);
        break;
    default:
        io_off(be_motor_fwd_io);
        io_off(be_motor_rev_io);
        break;
    }
}

static inline void be_motor_parking(void)
{
    while(!is_cam_bottom_pressed())
    {
        be_motor(BE_MOT_DIR_REV);
    }

    be_motor(BE_MOT_DIR_STOP);
    _delay_ms(200);

    while(!(is_cam_top_pressed() && !is_cam_bottom_pressed()))
    {
        be_motor(BE_MOT_DIR_FWD);
    }

    be_motor(BE_MOT_DIR_STOP);
    _delay_ms(10);
}

static inline void be_motor_parking_after_brew(void)
{
    be_motor(BE_MOT_DIR_REV);
    _delay_ms(500);

    be_motor_parking();
}

static inline void be_motor_parking_on_startup(void)
{
    be_motor(BE_MOT_DIR_FWD);
    _delay_ms(1200);

    be_motor(BE_MOT_DIR_STOP);
    _delay_ms(100);

    be_motor(BE_MOT_DIR_REV);
    _delay_ms(900);

    be_motor_parking();
}


static inline void be_motor_press(void)
{
    be_motor(BE_MOT_DIR_FWD);
    _delay_ms(500);

    while(!is_cam_top_pressed())
    {
        be_motor(BE_MOT_DIR_FWD);
    }

    while(!(!is_cam_top_pressed() && is_cam_bottom_pressed()))
    {
        be_motor(BE_MOT_DIR_FWD);
    }

    be_motor(BE_MOT_DIR_STOP);
}

static inline void be_motor_unpress(void)
{
    while(!(is_cam_top_pressed() && is_cam_bottom_pressed()))
    {
        be_motor(BE_MOT_DIR_REV);
    }

    be_motor(BE_MOT_DIR_STOP);
}

#endif // PERIPH_H_