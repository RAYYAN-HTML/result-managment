cmake_minimum_required(VERSION 3.10)
project(ResultManagement)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Student.cpp
    src/Utils.cpp
    src/ResultCalculator.cpp
    src/DatabaseManager.cpp
    src/User.cpp
    src/ResultManager.cpp
)

# Create executable
add_executable(result_management ${SOURCES})

# Compiler flags
if(MSVC)
    target_compile_options(result_management PRIVATE /W4)
else()
    target_compile_options(result_management PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Output directory
set_target_properties(result_management PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
