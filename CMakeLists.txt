cmake_minimum_required(VERSION 3.14)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_COMPILER   /opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /opt/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-g++)
set (CMAKE_CXX_STANDARD 11)
PROJECT(dust_sucker CXX C ASM)


add_compile_options(-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -Wall -ffunction-sections)

add_link_options(-specs=nosys.specs
    -Wl,--gc-sections -T/mnt/c/gitrepo/DustSucker/STM32H743ZITx_FLASH.ld
    -lc -lm -lnosys
    -Wl,-Map=dust_sucker.map,--cref
    -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard
    -Wall -fdata-sections -ffunction-sections)


add_executable(dust_sucker 
    Src/main.cpp
    Src/stm32h7xx_it.c 
    Src/stm32h7xx_hal_msp.c 
    Src/system_stm32h7xx.c  
    STM32H743ZITx_FLASH.ld)

add_subdirectory(STM32Cube_FW_H7_V1.3.0)

target_include_directories(dust_sucker PUBLIC
    Inc
    STM32Cube_FW_H7_V1.3.0/STM32H7xx_HAL_Driver/Inc
    STM32Cube_FW_H7_V1.3.0/STM32H7xx_HAL_Driver/Inc/Legacy
    STM32Cube_FW_H7_V1.3.0/CMSIS/Device/ST/STM32H7xx/Include
    STM32Cube_FW_H7_V1.3.0/CMSIS/Include
    STM32Cube_FW_H7_V1.3.0/CMSIS/Include)
target_link_libraries( dust_sucker PUBLIC hal_stm32h7)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
    COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

