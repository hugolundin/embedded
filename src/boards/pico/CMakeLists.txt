file(GLOB PICO_SOURCES ${PROJECT_SOURCE_DIR}/src/boards/pico/*.c)

add_pico_executable(
    main
    ${PICO_SOURCES}
)

target_link_libraries(
    main
    libshared
    libdrivers
)
