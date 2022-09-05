file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests/*.c)

add_executable(
    test_runner
    ${TEST_SOURCES}
)

target_link_libraries(
    test_runner
    unity
    libshared
    libdrivers
)

target_include_directories(
    test_runner
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

add_test(tests test_runner)
