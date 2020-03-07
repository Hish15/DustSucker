cmake_minimum_required(VERSION 3.14)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set (CMAKE_CXX_STANDARD 11)
PROJECT(dust_sucker.elf CXX C ASM)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -Wall -ffunction-sections)

add_link_options(-specs=nano.specs -u _printf_float
    -Wl,--gc-sections -T${CMAKE_SOURCE_DIR}/STM32H743ZITx_FLASH.ld
    -lc -lm -lnosys
    -Wl,-Map=dust_sucker.map,--cref
    -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard
    -Wall -fdata-sections -ffunction-sections)


add_executable(dust_sucker.elf
    Src/syscalls.c
    Src/gpio.c
    Src/tim.c
    Src/i2c.c
    Src/usart.c
    Src/main.c
    Src/main.cpp
    Src/stm32h7xx_it.c 
    Src/stm32h7xx_hal_msp.c 
    Src/system_stm32h7xx.c  
    Src/wheel.cpp
    STM32H743ZITx_FLASH.ld
    Src/usbd_cdc_if.c
    Src/usbd_conf.c
    Src/usbd_desc.c
    Src/usb_device.c
)
target_include_directories(dust_sucker.elf PUBLIC
    Inc
    STM32Cube_FW_H7_V1.4.0/STM32H7xx_HAL_Driver/Inc
    STM32Cube_FW_H7_V1.4.0/STM32H7xx_HAL_Driver/Inc/Legacy
    STM32Cube_FW_H7_V1.4.0/CMSIS/Device/ST/STM32H7xx/Include
    STM32Cube_FW_H7_V1.4.0/CMSIS/Include
    STM32Cube_FW_H7_V1.4.0/CMSIS/Include)

add_subdirectory(STM32_USB_Device_Library)
target_link_libraries(dust_sucker.elf PUBLIC stm32_usb_device)

add_subdirectory(STM32Cube_FW_H7_V1.4.0)
target_link_libraries( dust_sucker.elf PUBLIC hal_stm32h7)
add_subdirectory(ST-VL53L1X)
target_link_libraries(vl53l1x PUBLIC hal_stm32h7)

target_link_libraries( dust_sucker.elf PUBLIC vl53l1x)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    #COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
	COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}"
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin)
	
set(JLINK_FILE "${CMAKE_CURRENT_BINARY_DIR}/flash_${PROJECT_NAME}.jlink")
file(WRITE "${JLINK_FILE}"
	"loadbin ${PROJECT_NAME}.bin,0x08000000\n"
	"r\n"
	"go\n"
    "exit")
add_custom_target(flash
	COMMENT "Trying to flash the device with ${PROJECT_NAME} at 0x08000000"
    COMMAND JLink.exe -device "STM32H743ZI" -autoconnect 1 -If SWD -Speed 4000  -ExitOnError -CommandFile "flash_${PROJECT_NAME}.jlink"
    DEPENDS dust_sucker.elf)

