cmake_minimum_required(VERSION 3.20)

# Project name will be replaced by init script
project(Potato_Template VERSION 1.0.0 LANGUAGES CXX)

# C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type setup
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Fast compilation: minimal debug info, no optimization
    set(CMAKE_CXX_FLAGS_DEBUG "-g1 -O0")
    message(STATUS "Debug mode: Fast compilation enabled")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Maximum performance: aggressive optimization, LTO, native arch
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -DNDEBUG")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    message(STATUS "Release mode: Maximum performance enabled")
endif()

# Warning flags (applies to both modes)
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
)

# Find raylib
find_package(raylib 5.0 REQUIRED)

# Find raylib-cpp (header-only, installed via yay)
find_path(RAYLIB_CPP_INCLUDE_DIR raylib-cpp.hpp
    PATHS /usr/include /usr/local/include
    REQUIRED
)

# Core static library
file(GLOB_RECURSE CORE_SOURCES "core/src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS "core/include/*.hpp" "core/include/*.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core/include
        ${RAYLIB_CPP_INCLUDE_DIR}
)

target_link_libraries(core
    PUBLIC
        raylib
)

# Set core library properties
set_target_properties(core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# App executable
file(GLOB_RECURSE APP_SOURCES "App/src/*.cpp")
file(GLOB_RECURSE APP_HEADERS "App/include/*.hpp" "App/include/*.h")

add_executable(Potato_Template ${APP_SOURCES} ${APP_HEADERS})

target_include_directories(Potato_Template
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/App/include
)

target_link_libraries(Potato_Template
    PRIVATE
        core
)

# Set executable properties
set_target_properties(Potato_Template PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print build info
message(STATUS "===========================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "===========================================")
