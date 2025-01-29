set(PROJECT  pico_cli)
cmake_minimum_required(VERSION 3.12)
set(PICO_BOARD pico)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PROJECT} C CXX)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
#set(PICO_USE_STACK_GUARDS 1)
pico_sdk_init()
add_executable(pico_cli main.cpp)

target_sources(${PROJECT} PRIVATE
        main.cpp
        Prompt.cpp
        )
target_include_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT}
     pico_stdlib
     pico_multicore

)

pico_add_extra_outputs(${PROJECT})

pico_enable_stdio_usb(${PROJECT} 1)  # Enable USB serial for stdio
pico_enable_stdio_uart(${PROJECT} 0) # Disable UART for stdio

