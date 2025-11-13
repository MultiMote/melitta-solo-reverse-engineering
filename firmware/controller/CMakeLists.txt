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


include_directories(libs/cmsis-core/Include)
include_directories(libs/cmsis-device-f1/Include)

set(CMAKE_EXE_LINKER_FLAGS "${STM32_FLAGS} -T${PROJECT_SOURCE_DIR}/init/STM32F103XB_FLASH.ld")

add_executable(${TARGET}
    main.c
    syscalls.c
    init/startup_stm32f103xb.s
    init/system_stm32f1xx.c
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
