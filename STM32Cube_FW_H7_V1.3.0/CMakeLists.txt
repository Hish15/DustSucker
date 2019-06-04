add_library(hal_stm32h7 "")
target_compile_options(hal_stm32h7 PUBLIC
    -mthumb -fno-builtin -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -Wall -std=gnu99 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize)

#target_link_libraries(DustSucker VL53L1X "-specs=nosys.specs -specs=nano.specs -u _printf_float")

target_compile_definitions(hal_stm32h7 PUBLIC STM32H743xx)

add_subdirectory(STM32H7xx_HAL_Driver)

target_include_directories(hal_stm32h7 
    PRIVATE .
    CMSIS/Device/ST/STM32H7xx/Include
    CMSIS/Include)

set_target_properties(hal_stm32h7
    PROPERTIES
        OUTPUT_NAME "hal_stm32h7.bin"
        PREFIX ""
        SUFFIX "")
