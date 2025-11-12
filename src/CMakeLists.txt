cmake_minimum_required(VERSION 4.1)

project(melitta)

set(TARGET ${PROJECT_NAME}.elf)

enable_language(ASM)

SET(STM32_FLAGS "
    -DSTM32F103xB \
    -march=armv7-m \
    -mcpu=cortex-m3 \
    -mthumb \
    -mlittle-endian \
    -ffunction-sections \
    -fdata-sections \
    -mfloat-abi=soft \
    -Wall -Werror \
    -Wl,-Map=output.map -Wl,--gc-sections \
    -lm -lc")

set(CMAKE_C_FLAGS "${STM32_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${STM32_FLAGS} -O2")
set(CMAKE_ASM_FLAGS "-march=armv7-m -mcpu=cortex-m3 -mthumb -mlittle-endian")


include_directories(CMSIS/Include)
include_directories(CMSIS/Device/ST/STM32F1xx/Include)

set(CMAKE_EXE_LINKER_FLAGS "${STM32_FLAGS} -T${PROJECT_SOURCE_DIR}/sys/STM32F103XB_FLASH.ld")

add_executable(${TARGET}
    main.c
    syscalls.c
    sys/startup_stm32f103xb.s
    CMSIS/Device/ST/STM32F1xx/Source/system_stm32f1xx.c
)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley ${TARGET}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)