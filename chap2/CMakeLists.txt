cmake_minimum_required(VERSION 3.10)

# Project metadata
project(chap2_practice VERSION 1.0 LANGUAGES CXX)

# Set C++ standard 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Gather all .cpp files in src and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 2. Tell CMake where the headers are
include_directories(include)

# 3. Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 4. Enable useful compiler warnings 
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
