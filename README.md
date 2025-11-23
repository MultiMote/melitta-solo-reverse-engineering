The project is about the reverse engineering of the Mellita Solo Perfect Milk coffee machine.

Both of MCUs in my device are dead so I want try to make own controller.

[Schematics](schematics)

⚠⚠⚠

The board is not galvanically isolated from the mains (AC220_N connected to +5V)! Disconnect the programmer from the computer when applying mains voltage to the board, otherwise something may blow up!

Or:

  - Use laptop with battery power

  - Power up board using transformer only (disconnect transformer from "Trafo" connector and connect transformer to 220v)

⚠⚠⚠

## EF693 Main

MCU is ATmega324PA (TQFP)

Top:

![ef693_main_top](images/ef693_main_top.jpg)

Under RJ12 (6P6C) connector:

![ef693_main_top_rj12](images/ef693_main_top_rj12.jpg)

Bottom:

![ef693_main_bot](images/ef693_main_bottom.jpg)

Wiring:

![ef693_main_wiring](images/ef693_main_wiring.jpg)

MCU Pins:

![mcu_pins_main](images/mcu_pins_main.jpg)

## EF693 Disp

MCU is ATtiny48AU (TQFP)

Top:

![ef693_disp_top](images/ef693_disp_top.jpg)

Bottom:

![ef693_disp_bot](images/ef693_disp_bot.jpg)

MCU Pins:

![mcu_pins](images/mcu_pins_disp.jpg)

For this project, I have replaced the ATtiny48A with the ATmega328P, which is often used in Arduino boards. The pinout is mostly compatible, but one modification is necessary.

![ef693_disp_mod](images/ef693_disp_mod.jpg)

## Brewing unit actuator

Work of cam mechanism - power on (parking)

[source](https://www.youtube.com/watch?v=c8QlqGzTjy4)

https://github.com/user-attachments/assets/4184253f-a59c-4510-841d-e7e167fd1758
