set(CMAKE_SYSTEM_NAME      Generic)

if(TOOLCHAIN_BIN_DIR AND NOT TOOLCHAIN_BIN_DIR MATCHES ".*[/\\\\]$")
    set(TOOLCHAIN_BIN_DIR "${TOOLCHAIN_BIN_DIR}/")
endif()

if (WIN32)
    set(TOOLCHAIN_BIN_SUFFIX ".exe")
endif()

SET(CMAKE_AR           ${TOOLCHAIN_BIN_DIR}arm-none-eabi-gcc-ar${TOOLCHAIN_BIN_SUFFIX}     )
SET(CMAKE_RANLIB       ${TOOLCHAIN_BIN_DIR}arm-none-eabi-gcc-ranlib${TOOLCHAIN_BIN_SUFFIX} )
SET(CMAKE_LD           ${TOOLCHAIN_BIN_DIR}arm-none-eabi-ld${TOOLCHAIN_BIN_SUFFIX}         )
set(CMAKE_C_COMPILER   ${TOOLCHAIN_BIN_DIR}arm-none-eabi-gcc${TOOLCHAIN_BIN_SUFFIX}        )
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}arm-none-eabi-g++${TOOLCHAIN_BIN_SUFFIX}        )
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}arm-none-eabi-as${TOOLCHAIN_BIN_SUFFIX}         )
set(CMAKE_OBJCOPY      ${TOOLCHAIN_BIN_DIR}arm-none-eabi-objcopy${TOOLCHAIN_BIN_SUFFIX}    )
set(CMAKE_OBJDUMP      ${TOOLCHAIN_BIN_DIR}arm-none-eabi-objdump${TOOLCHAIN_BIN_SUFFIX}    )
set(CMAKE_GDB          ${TOOLCHAIN_BIN_DIR}arm-none-eabi-gdb${TOOLCHAIN_BIN_SUFFIX}        )
set(CMAKE_SIZE         ${TOOLCHAIN_BIN_DIR}arm-none-eabi-size${TOOLCHAIN_BIN_SUFFIX}       )


set(COMPILER_OPTIONS "-mthumb -mcpu=cortex-m3 -mlittle-endian")
SET(CMAKE_C_FLAGS "${COMPILER_OPTIONS} -lm -lc -lnosys --specs=nosys.specs")
SET(CMAKE_CXX_FLAGS "${COMPILER_OPTIONS} -lm -lc -lnosys --specs=nosys.specs")
SET(CMAKE_EXE_LINKER_FLAGS "${COMPILER_OPTIONS} -Wl,-Map=linker.map -Wl,-cref -Wl,--gc-sections")
