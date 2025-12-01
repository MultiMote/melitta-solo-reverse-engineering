#ifndef PERIPH_H_
#define PERIPH_H_

#include <avr/io.h>
#include <util/delay.h>

#include "utils.h"

#define BE_MOT_PORT PORTC
#define BE_MOT_DDR DDRC
#define BE_MOT_FWD_PIN PORTC6
#define BE_MOT_REV_PIN PORTC7

#define BE_CAM_TOP_DDR PORTA
#define BE_CAM_TOP_PINR PINA
#define BE_CAM_TOP_PIN PORTA5

#define BE_CAM_BOTTOM_DDR PORTB
#define BE_CAM_BOTTOM_PINR PINB
#define BE_CAM_BOTTOM_PIN PORTB0

#define BE_PRESS_DDR PORTA
#define BE_PRESS_PINR PINA
#define BE_PRESS_PIN PORTA6



enum be_motor_dir_t
{
    BE_MOT_DIR_STOP = 0,
    BE_MOT_DIR_FWD,
    BE_MOT_DIR_REV
};

static inline void hw_init(void)
{
    BE_MOT_DDR |= _BV(BE_MOT_FWD_PIN) | _BV(BE_MOT_REV_PIN);

    BE_CAM_TOP_DDR &= ~_BV(BE_CAM_TOP_PIN);
    BE_CAM_BOTTOM_DDR &= ~_BV(BE_CAM_BOTTOM_PIN);
    BE_PRESS_DDR &= ~_BV(BE_PRESS_PIN);
}

static inline uint8_t is_cam_top_pressed(void)
{
    return !pin_check(BE_CAM_TOP_PINR, _BV(BE_CAM_TOP_PIN));
}

static inline uint8_t is_cam_bottom_pressed(void)
{
    return !pin_check(BE_CAM_BOTTOM_PINR, _BV(BE_CAM_BOTTOM_PIN));
}

static inline uint8_t is_press_pressed(void)
{
    return !pin_check(BE_PRESS_PINR, _BV(BE_PRESS_PIN));
}

static inline void be_motor(enum be_motor_dir_t dir)
{
    switch (dir)
    {
    case BE_MOT_DIR_FWD:
        pin_on(BE_MOT_PORT, _BV(BE_MOT_FWD_PIN));
        pin_off(BE_MOT_PORT, _BV(BE_MOT_REV_PIN));
        break;
    case BE_MOT_DIR_REV:
        pin_on(BE_MOT_PORT, _BV(BE_MOT_REV_PIN));
        pin_off(BE_MOT_PORT, _BV(BE_MOT_FWD_PIN));
        break;
    default:
        pin_off(BE_MOT_PORT, _BV(BE_MOT_FWD_PIN) | _BV(BE_MOT_REV_PIN));
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
    _delay_ms(100);

    while(!is_cam_top_pressed()) // not pressed
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
    _delay_ms(800);

    be_motor(BE_MOT_DIR_STOP);
    _delay_ms(200);

    be_motor(BE_MOT_DIR_REV);
    _delay_ms(500);

    be_motor_parking();
}


static inline void be_motor_press(void)
{
    be_motor(BE_MOT_DIR_FWD);
    _delay_ms(500);

    while(!is_cam_bottom_pressed() && !is_press_pressed())
    {
        be_motor(BE_MOT_DIR_FWD);
    }

    be_motor(BE_MOT_DIR_STOP);
}

#endif // PERIPH_H_