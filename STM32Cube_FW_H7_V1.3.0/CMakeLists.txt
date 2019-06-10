add_library(hal_stm32h7 "")

#target_link_libraries(DustSucker VL53L1X "-specs=nosys.specs -specs=nano.specs -u _printf_float")

target_compile_definitions(hal_stm32h7 PUBLIC USE_HAL_DRIVER STM32H743xx)

add_subdirectory(STM32H7xx_HAL_Driver)

set(STARTUP_FILE CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h743xx.s)
set_source_files_properties(${STARTUP_FILE} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

target_sources(hal_stm32h7 PRIVATE ${STARTUP_FILE})

target_include_directories(hal_stm32h7 
    PRIVATE 
        .
    PUBLIC
        CMSIS/Device/ST/STM32H7xx/Include
        CMSIS/Include)

set_target_properties(hal_stm32h7
    PROPERTIES
        OUTPUT_NAME "hal_stm32h7"
        PREFIX ""
        SUFFIX ".bin")
