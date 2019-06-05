cmake_minimum_required(VERSION 3.14)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

PROJECT(DustSucker)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

add_executable(dust_sucker.elf
    Src/main.c
    Src/stm32h7xx_hal_msp.c
    Src/stm32h7xx_it.c
    Src/system_stm32h7xx.c
    STM32H743ZITx_FLASH.ld 
    )
target_include_directories(dust_sucker.elf PUBLIC Inc)

add_subdirectory(STM32Cube_FW_H7_V1.3.0)

target_link_libraries(dust_sucker.elf PUBLIC
    --specs=nosys.specs
    hal_stm32h7)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_custom_target(dust_sucker.hex ALL DEPENDS dust_sucker.elf COMMAND ${CMAKE_OBJCOPY} -Oihex dust_sucker.elf dust_sucker.hex)

