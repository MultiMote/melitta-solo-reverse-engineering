Build

```
mkdir build
cd build
cmake -G Ninja -DTOOLCHAIN_BIN_DIR="path/to/compiler/bin" -DCMAKE_TOOLCHAIN_FILE="extra/arm-none-eabi-toolchain.cmake" ..
cmake --build .
```

Toolchain file example: [extra/arm-none-eabi-toolchain.cmake](extra/arm-none-eabi-toolchain.cmake)
