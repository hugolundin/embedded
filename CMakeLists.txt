cmake_minimum_required(VERSION 3.24)

set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (${BOARD} MATCHES "PICO")
    message(STATUS "Board: pico")

    set(CMAKE_C_COMPILER "/usr/local/bin/arm-none-eabi-gcc")

    if (NOT DEFINED ENV{PICO_SDK_PATH})
        message(FATAL_ERROR "PICO_SDK_PATH not set.")
    endif()
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
else()
    message(STATUS "Board: host")
    set(CMAKE_C_COMPILER "clang")
endif()

project(embedded C CXX ASM)

if (${BOARD} MATCHES "PICO")
    pico_sdk_init()

    function(add_pico_executable EXECUTABLE_NAME)
        set(elf_file ${EXECUTABLE_NAME}.elf)
        set(hex_file ${EXECUTABLE_NAME}.hex)

        add_executable(
            ${EXECUTABLE_NAME}
            ${ARGN}
        )
        
        add_custom_target(
            upload_${EXECUTABLE_NAME}
            openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program ${PROJECT_SOURCE_DIR}/build/pico/src/boards/pico/${elf_file} verify reset exit"
            DEPENDS ${elf_file}
        )

        add_custom_target(
            gdb_${EXECUTABLE_NAME}
            printf "arm-none-eabi-gdb --init-command=${PROJECT_SOURCE_DIR}/.gdbinit ${PROJECT_SOURCE_DIR}/build/pico/src/boards/pico/${elf_file}"
            DEPENDS ${elf_file}
        )


        # if (${DEBUGGER} MATCHES "PICO-DEBUG")
        #     add_custom_target(
        #         upload_${EXECUTABLE_NAME}
        #         openocd -f board/pico-debug.cfg -c "program ${PROJECT_SOURCE_DIR}/build/pico/src/boards/pico/${elf_file} verify reset exit"
        #         DEPENDS ${elf_file}
        #     )
        # else()
        #     add_custom_target(
        #         upload_${EXECUTABLE_NAME}
        #         openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -c "program ${PROJECT_SOURCE_DIR}/build/pico/src/boards/pico/${elf_file} verify reset exit"
        #         DEPENDS ${elf_file}
        #     )
        # endif()

        add_custom_target(
            debug_${EXECUTABLE_NAME}
            arm-none-eabi-gdb -ex 'target remote localhost:3333' ${PROJECT_SOURCE_DIR}/build/pico/src/${elf_file}
            DEPENDS ${elf_file}
        )

        target_link_libraries(
            ${EXECUTABLE_NAME}
            pico_stdlib
        )        

        pico_enable_stdio_usb(${EXECUTABLE_NAME} 0)
        pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)
        pico_enable_stdio_semihosting(${EXECUTABLE_NAME} 0)
        pico_add_extra_outputs(${EXECUTABLE_NAME})
    endfunction(add_pico_executable)
endif()

add_subdirectory(src)

if (NOT ${BOARD} MATCHES "PICO")
    include(CTest)
    add_subdirectory($ENV{UNITY_PATH} unity)
    add_subdirectory(tests)

    message(STATUS "Tests added")
endif()
