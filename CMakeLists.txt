cmake_minimum_required(VERSION 3.22)

project(
    TinyMLL
    VERSION 0.0.1
    DESCRIPTION "TinyMLL (Tiny Machine Learning Library)"
    LANGUAGES C
)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Generate compile_commands.json for vscode intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type is Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Summary
message(STATUS "")
message(STATUS "===============================")
message(STATUS "Build:      ${CMAKE_BUILD_TYPE}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Generator:  ${CMAKE_GENERATOR}")
message(STATUS "===============================")
message(STATUS "")

# Backend options
set(TINYMLL_BACKEND "TINYMLL_CPU" CACHE STRING "Choose TinyMLL Backend")
set_property(CACHE TINYMLL_BACKEND PROPERTY STRINGS "TINYMLL_CPU" "TINYMLL_CPU_SIMD" "TINYMLL_CPU_MT" "TINYMLL_GPU")

# Lib type options
set(TINYMLL_LIB_TYPE "STATIC" CACHE STRING "Build TinyMLL as")
set_property(CACHE TINYMLL_LIB_TYPE PROPERTY STRINGS "STATIC" "SHARED")

message(STATUS "")
message(STATUS "===============================")
message(STATUS "Building TinyMLL library ...")

# Sources
set(TINYMLL_SOURCES
    src/core/error.c
    src/core/random.c
)

# Backend sources and definitions
message(STATUS "TinyMLL Backend:   ${TINYMLL_BACKEND}")
if(TINYMLL_BACKEND STREQUAL "CPU_NAIVE")
    set(TINYMLL_BACKEND_SOURCES)
    set(TINYMLL_BACKEND_DEFS ${TINYMLL_BACKEND})

elseif(TINYMLL_BACKEND STREQUAL "CPU_SIMD")
    set(TINYMLL_BACKEND_SOURCES)
    set(TINYMLL_BACKEND_DEFS ${TINYMLL_BACKEND})

elseif(TINYMLL_BACKEND STREQUAL "CPU_MT")
    set(TINYMLL_BACKEND_SOURCES)
    set(TINYMLL_BACKEND_DEFS ${TINYMLL_BACKEND})

else() # GPU
    set(TINYMLL_BACKEND_SOURCES)
    set(TINYMLL_BACKEND_DEFS ${TINYMLL_BACKEND})

endif()

# Library creation
message(STATUS "TinyMLL Lib type:  ${TINYMLL_LIB_TYPE}")
add_library(tinymll ${TINYMLL_LIB_TYPE} ${TINYMLL_SOURCES} ${TINYMLL_BACKEND_SOURCES})

target_compile_definitions(tinymll PRIVATE ${TINYMLL_BACKEND_DEFS})
target_include_directories(tinymll PRIVATE include)
target_link_libraries(tinymll PRIVATE m)
target_compile_options(tinymll PRIVATE
    -Wall
    -Wextra
    -pedantic
)

message(STATUS "===============================")
message(STATUS "")
