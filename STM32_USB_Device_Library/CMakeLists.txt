cmake_minimum_required(VERSION 3.14)
add_library(stm32_usb_device INTERFACE)

target_sources(stm32_usb_device INTERFACE
    Core/Src/usbd_core.c
    Core/Src/usbd_ctlreq.c
    Core/Src/usbd_ioreq.c

    Class/CDC/Src/usbd_cdc.c
    )
target_include_directories(stm32_usb_device INTERFACE
    Core/Inc
    Class/CDC/Inc
    )


