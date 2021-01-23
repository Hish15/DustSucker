## Built with

This projects is built using arm-gcc.

## Dependencies

This projects uses the following projects

- stm32-cmake
- STM32CubeH7
- FreeRTOS (the one included in STM32CubeH7)

Version requirements are specified in the CMakeLists.txt file

## How to build

Run the following commands :

```
cmake -B build -G Ninja .
ninja -C build
```

The folder `build` will contain the freshly built firmware 


