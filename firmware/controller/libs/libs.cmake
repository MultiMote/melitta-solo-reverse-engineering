include_directories(libs/cmsis-core/Include)
include_directories(libs/cmsis-device-f1/Include)
include_directories(libs/stm32f1xx-hal-driver/Inc)

set(LL_MODULES adc dma gpio rcc tim usart utils)

foreach(mod IN LISTS LL_MODULES)
    list(APPEND OTHER_SOURCES libs/stm32f1xx-hal-driver/Src/stm32f1xx_ll_${mod}.c)
endforeach()
