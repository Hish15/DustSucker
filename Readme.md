## Built with

This projects is built using arm-gcc.

## Dependencies

This projects uses the following projects

- stm32-cmake
- STM32CubeH7
- FreeRTOS (the one included in STM32CubeH7)

Version requirements are specified in the CMakeLists.txt file

## How to build

This project contains a Dockerfile to allow to build easily and with all dependencies.
Running the container will call cmake on a volume mounted to the container /usr/src/app folder

To use it the commands are :

```
docker build -t dustsucker . &&
docker run --mount .:usr/src/app dustsucker
```

An shortend way is to use docker-compose :

```
docker-compose up
```
