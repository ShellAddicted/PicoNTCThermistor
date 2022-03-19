cmake_minimum_required(VERSION 3.12)

# Pull in Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

# Initialise the Pico SDK
pico_sdk_init()

add_library(PicoNTCThermistor INTERFACE)
target_sources(PicoNTCThermistor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/pico_ntc_thermistor.cpp)
target_include_directories(PicoNTCThermistor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(PicoNTCThermistor INTERFACE pico_stdlib)