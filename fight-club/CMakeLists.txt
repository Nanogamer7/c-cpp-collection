cmake_minimum_required(VERSION 3.21)

project(fight-club LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "fight-club.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Create executable
add_executable(fight-club ${SOURCES} ${HEADERS})

# Set include directories
target_include_directories(fight-club PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Add compiler flags
target_compile_options(fight-club PRIVATE -O3 -Wall -Wextra -Wpedantic -Wconversion)

# Add linker flags
target_link_options(fight-club PRIVATE)

# Set build type to release
set(CMAKE_BUILD_TYPE Release)
