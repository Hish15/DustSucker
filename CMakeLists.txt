cmake_minimum_required(VERSION 3.13)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/stm32-cmake/cmake/stm32_gcc.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(STM32_CUBE_H7_PATH ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeH7) 
set(FREERTOS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeH7/Middlewares/Third_Party/FreeRTOS)

project(DustSucker C ASM)

#Find CMSIS for both cores
find_package(HAL COMPONENTS STM32H743ZI_M7 REQUIRED)
find_package(CMSIS COMPONENTS STM32H743ZI_M7 REQUIRED)
find_package(FreeRTOS COMPONENTS ARM_CM7)

#Check HAL/CMSIS Version
message(STATUS "CMSIS_VERSION is ${CMSIS_VERSION}")
if(CMSIS_VERSION VERSION_EQUAL "5.4.0")
    #All good
else()
    message(FATAL_ERROR "Wrong CMSIS version found, check ST HAL version") 
endif()

#Creating both binaries
add_executable(dustSucker Src/main.c)
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
ADD_CUSTOM_TARGET(do_always ALL COMMAND ${CMAKE_OBJCOPY} -O ihex dustSucker dustSucker.hex
                                DEPENDS dustSucker)
