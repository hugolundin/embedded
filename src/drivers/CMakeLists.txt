file(GLOB LIBDRIVERS_SOURCES ${PROJECT_SOURCE_DIR}/src/drivers/*.c)

add_library(
    libdrivers
    STATIC 
    ${LIBDRIVERS_SOURCES}
)

target_include_directories(libdrivers PUBLIC ${PROJECT_SOURCE_DIR}/src/libdrivers)
