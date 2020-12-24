cmake_minimum_required(VERSION 3.13)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/stm32-cmake/cmake/stm32_gcc.cmake)

set(STM32_CUBE_H7_PATH ${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeH7) 
project(DustSucker C ASM)

#Find CMSIS for both cores
find_package(HAL COMPONENTS STM32H757VG_M7 REQUIRED)
find_package(CMSIS COMPONENTS STM32H757VG_M7 REQUIRED)

#Creating both binaries
add_executable(dustSucker Src/main.c)
target_include_directories(dustSucker PRIVATE Inc)

target_include_directories(dustSucker PRIVATE Inc)
target_include_directories(dustSucker PRIVATE Inc)

target_link_libraries(dustSucker PRIVATE
    HAL::STM32::H7::M7::CORTEX
    CMSIS::STM32::H757VG::M7
    STM32::NoSys
    )

