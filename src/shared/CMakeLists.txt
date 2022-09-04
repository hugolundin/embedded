file(GLOB LIBSHARED_SOURCES ${PROJECT_SOURCE_DIR}/src/shared/*.c)

add_library(
    libshared 
    STATIC 
    ${LIBSHARED_SOURCES}
)

target_include_directories(libshared PUBLIC ${PROJECT_SOURCE_DIR}/src/libshared)
