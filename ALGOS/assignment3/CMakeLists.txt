cmake_minimum_required(VERSION 3.21)

project(find_path LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Create executable
add_executable(find_path ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(find_path PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

# Set build type and corresponding flags
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(find_path PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    set_target_properties(find_path PROPERTIES LINK_FLAGS ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
else()
    target_compile_options(find_path PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    set_target_properties(find_path PROPERTIES LINK_FLAGS ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
endif()
