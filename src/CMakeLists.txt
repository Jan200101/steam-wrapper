set(C_STANDARD 99)

set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/common.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(core STATIC ${CORE_SOURCES})

foreach(VER ${VERSIONS})
    if(COMPILE_${VER})
        string(TOLOWER ${VER} VER_LOWER)
        add_subdirectory(${VER_LOWER})
    endif()
endforeach()