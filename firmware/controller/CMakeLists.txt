cmake_minimum_required(VERSION 4.1)

project(melitta)
enable_language(ASM)

find_program(OPENOCD openocd)


set(TARGET ${PROJECT_NAME}.elf)


SET(STM32_FLAGS "
    -DSTM32F103xB \
    -DUSE_FULL_LL_DRIVER \
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
set(CMAKE_EXE_LINKER_FLAGS "${STM32_FLAGS} -T${PROJECT_SOURCE_DIR}/init/STM32F103XB_FLASH.ld")

set(OTHER_SOURCES
    init/startup_stm32f103xb.s
    init/system_stm32f1xx.c
)

include(libs/libs.cmake)

add_executable(${TARGET}
    main.c
    syscalls.c
    ${OTHER_SOURCES}
)

set_property(TARGET ${TARGET} PROPERTY C_STANDARD 11)

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


if (OPENOCD)
  add_custom_target(flash-openocd
    COMMAND ${OPENOCD} -d0 -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program ${TARGET} verify reset exit"
    DEPENDS ${TARGET}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  )
endif()
