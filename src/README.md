Build

```
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="path/to/toolchain.cmake" ..
cmake --build .
```

Toolchain file example (Windows):

```
set(CMAKE_SYSTEM_NAME      Generic)

if (NOT TOOLCHAIN_BASE)
    set(TOOLCHAIN_BASE "D:/_COMPILERS/arm-gnu-toolchain-14.3.rel1-mingw-w64-i686-arm-none-eabi")
endif()

SET(CMAKE_AR               ${TOOLCHAIN_BASE}/bin/arm-none-eabi-gcc-ar.exe     )
SET(CMAKE_RANLIB           ${TOOLCHAIN_BASE}/bin/arm-none-eabi-gcc-ranlib.exe )
SET(CMAKE_LD               ${TOOLCHAIN_BASE}/bin/arm-none-eabi-ld.exe         )
set(CMAKE_C_COMPILER       ${TOOLCHAIN_BASE}/bin/arm-none-eabi-gcc.exe        )
set(CMAKE_CXX_COMPILER     ${TOOLCHAIN_BASE}/bin/arm-none-eabi-g++.exe        )
set(CMAKE_ASM_COMPILER     ${TOOLCHAIN_BASE}/bin/arm-none-eabi-as.exe         )
set(CMAKE_OBJCOPY          ${TOOLCHAIN_BASE}/bin/arm-none-eabi-objcopy.exe    )
set(CMAKE_OBJDUMP          ${TOOLCHAIN_BASE}/bin/arm-none-eabi-objdump.exe    )
set(CMAKE_GDB              ${TOOLCHAIN_BASE}/bin/arm-none-eabi-gdb.exe        )
set(CMAKE_SIZE             ${TOOLCHAIN_BASE}/bin/arm-none-eabi-size.exe       )


set(COMPILER_OPTIONS "-mthumb -mcpu=cortex-m3 -mlittle-endian")
SET(CMAKE_C_FLAGS "${COMPILER_OPTIONS} -lm -lc -lnosys --specs=nosys.specs")
SET(CMAKE_CXX_FLAGS "${COMPILER_OPTIONS} -lm -lc -lnosys --specs=nosys.specs")
SET(CMAKE_EXE_LINKER_FLAGS "${COMPILER_OPTIONS} -Wl,-Map=linker.map -Wl,-cref -Wl,--gc-sections")
```
