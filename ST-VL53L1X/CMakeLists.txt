add_library(vl53l1x STATIC)
target_sources(vl53l1x PRIVATE 
    api/core/vl53l1_api.c
    api/core/vl53l1_api_calibration.c
    api/core/vl53l1_api_core.c
    api/core/vl53l1_api_debug.c
    api/core/vl53l1_api_preset_modes.c
    api/core/vl53l1_api_strings.c
    api/core/vl53l1_core.c
    api/core/vl53l1_core_support.c
    api/core/vl53l1_error_strings.c
    api/core/vl53l1_register_funcs.c
    api/core/vl53l1_silicon_core.c
    api/core/vl53l1_wait.c
    api/platform/vl53l1_platform.c)
target_include_directories(vl53l1x PUBLIC 
    api/core
    api/platform)
