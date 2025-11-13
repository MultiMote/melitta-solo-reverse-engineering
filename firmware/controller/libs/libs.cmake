include_directories(libs/cmsis-core/Include)
include_directories(libs/cmsis-device-f1/Include)
include_directories(libs/stm32f1xx-hal-driver/Inc)

list(APPEND OTHER_SOURCES
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_adc.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_cortex.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_dma.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_flash.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_gpio.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_rcc.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_tim.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_hal_usart.c
)
