include_directories(libs/cmsis-core/Include)
include_directories(libs/cmsis-device-f1/Include)
include_directories(libs/stm32f1xx-hal-driver/Inc)

list(APPEND OTHER_SOURCES
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_adc.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_dma.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_gpio.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_rcc.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_tim.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_usart.c
    libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_utils.c
)
