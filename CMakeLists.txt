cmake_minimum_required(VERSION 3.14)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)
PROJECT(DustSucker)

set(CMAKE_C_COMPILER   /opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-g++)

add_subdirectory(STM32Cube_FW_H7_V1.3.0)


