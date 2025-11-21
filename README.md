The project is about the reverse engineering of the Mellita Solo Perfect Milk coffee machine.

Both of MCUs in my device are dead so I want try to make own controller.

[Schematics](schematics)

## EF693 Main

MCU is ATmega324PA (TQFP)

![ef693_main_top](images/ef693_main_top.jpg)

![ef693_main_bot](images/ef693_main_bottom.jpg)

Wiring:

![ef693_main_wiring](images/ef693_main_wiring.jpg)

MCU Pins:

![mcu_pins_main](images/mcu_pins_main.jpg)

## EF693 Disp

MCU is ATtiny48AU (TQFP)

![ef693_disp_top](images/ef693_disp_top.jpg)

![ef693_disp_bot](images/ef693_disp_bot.jpg)

MCU Pins:

![mcu_pins](images/mcu_pins_disp.jpg)

For this project, I have replaced the ATtiny48A with the ATmega328P, which is often used in Arduino boards. The pinout is mostly compatible, but one modification is necessary.

![ef693_disp_mod](images/ef693_disp_mod.jpg)
