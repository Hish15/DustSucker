cmake_minimum_required(VERSION 3.13)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/stm32-cmake/cmake/stm32_gcc.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


project(DustSucker ASM C CXX)
set(STM32_CUBE_H7_PATH /opt/STM32CubeH7)
#Use freertos from STM32CubeH7
set(FREERTOS_PATH ${STM32_CUBE_H7_PATH}/Middlewares/Third_Party/FreeRTOS)

#Find CMSIS for both cores
find_package(HAL 1.8.0 EXACT COMPONENTS STM32H743ZI_M7 REQUIRED)
find_package(CMSIS COMPONENTS STM32H743ZI_M7 REQUIRED )


find_package(FreeRTOS COMPONENTS ARM_CM7)

#Creating both binaries
add_executable(dustSucker Src/main.cpp)
target_include_directories(dustSucker PRIVATE Inc)

target_link_libraries(dustSucker PRIVATE
    FreeRTOS::Timers
    FreeRTOS::Heap::1
    FreeRTOS::ARM_CM7
    HAL::STM32::H7::M7::CORTEX
    CMSIS::STM32::H743ZI::M7
    HAL::STM32::H7::M7::RCC
    HAL::STM32::H7::M7::GPIO
    STM32::NoSys
    )
ADD_CUSTOM_TARGET(do_always ALL COMMAND ${CMAKE_OBJCOPY} -O ihex dustSucker.elf dustSucker.hex
                                DEPENDS dustSucker)
