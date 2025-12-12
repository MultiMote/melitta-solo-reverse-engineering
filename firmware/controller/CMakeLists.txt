cmake_minimum_required(VERSION 3.28)

project(melitta-controller)

set(TARGET ${PROJECT_NAME}.elf)

set(AVR_DEVICE atmega32a)
set(AVR_FREQ 8000000)

set(AVRDUDE_DEVICE m32)
set(AVRDUDE_FUSEBIT_FLAGS -U lfuse:w:0xEE:m -U hfuse:w:0x99:m)

if(NOT AVRDUDE_FLAGS)
    # usbasp programmer
    set(AVRDUDE_FLAGS -c usbasp -P usb -B 31.25 -V)
endif()


# Force release build
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
set(AVR_FLAGS "-mmcu=${AVR_DEVICE} \
    -DF_CPU=${AVR_FREQ}UL \
    -Wall \
    -Werror \
    -ffunction-sections \
    -fdata-sections \
    -Wl,--gc-sections")
set(CMAKE_C_FLAGS  "${AVR_FLAGS}")
set(CMAKE_CXX_FLAGS "${AVR_FLAGS}")

add_executable(${TARGET}
    main.c
)

set_property(TARGET ${TARGET} PROPERTY C_STANDARD 11)

# Print memory usage
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -Pmem-usage ${TARGET}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Extract HEX
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R.eeprom ${TARGET} ${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Extract EEPROM HEX
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${TARGET} ${PROJECT_NAME}-EEPROM.hex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

find_program(AVRDUDE_EXECUTABLE avrdude)

if (AVRDUDE_EXECUTABLE)
    add_custom_target(
        flash
        COMMAND ${AVRDUDE_EXECUTABLE} -s -p ${AVRDUDE_DEVICE} ${AVRDUDE_FLAGS} -U "flash:w:${PROJECT_NAME}.hex:a"
        DEPENDS ${TARGET}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )

    add_custom_target(
        flash-fusebits
        COMMAND ${AVRDUDE_EXECUTABLE} -s -p ${AVRDUDE_DEVICE} ${AVRDUDE_FLAGS} ${AVRDUDE_FUSEBIT_FLAGS}
        DEPENDS ${TARGET}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()
