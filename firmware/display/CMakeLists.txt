cmake_minimum_required(VERSION 4.1)

project(melitta-display)

set(TARGET ${PROJECT_NAME}.elf)

set(AVR_DEVICE atmega328p)
set(AVR_FREQ 8000000)

# Force release build
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
set(AVR_FLAGS "
    -mmcu=${AVR_DEVICE} \
    -DF_CPU=${AVR_FREQ}UL \
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

# Extract EEPRPOM HEX
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${TARGET} ${PROJECT_NAME}-EEPROM.hex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
