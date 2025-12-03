#ifndef PERIPH_H_
#define PERIPH_H_

#include <avr/io.h>
#include <util/delay.h>

#include "utils.h"

enum be_motor_dir_t
{
    BE_MOT_DIR_STOP = 0,
    BE_MOT_DIR_FWD,
    BE_MOT_DIR_REV
};

static const io_def_t be_motor_fwd_io  = IO_BUILD(C, 6);
static const io_def_t be_motor_rev_io  = IO_BUILD(C, 7);
static const io_def_t be_cam_top_io    = IO_BUILD(A, 5);
static const io_def_t be_cam_bottom_io = IO_BUILD(B, 0);
static const io_def_t be_cam_press_io  = IO_BUILD(A, 6);

static inline void hw_init(void)
{
    configure_output(be_motor_fwd_io);
    configure_output(be_motor_rev_io);

    configure_input(be_cam_top_io);
    configure_input(be_cam_bottom_io);
    configure_input(be_cam_press_io);
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