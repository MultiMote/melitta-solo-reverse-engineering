Build

```
mkdir build
cd build
cmake -G Ninja -DTOOLCHAIN_BIN_DIR="path/to/compiler/bin/" -DCMAKE_TOOLCHAIN_FILE="extra/avr8-gnu-toolchain.cmake" ..
cmake --build .
```

Toolchain file example: [extra/avr8-gnu-toolchain.cmake](extra/avr8-gnu-toolchain.cmake)

VSCode example (`.vscode/settings.json`):

```json
{
    "cmake.configureSettings": {
      "TOOLCHAIN_BIN_DIR": "path/to/compiler/bin/",
      "CMAKE_TOOLCHAIN_FILE": "extra/avr8-gnu-toolchain.cmake"
    },
    "cmake.generator": "Ninja"
}
```
