cmake_minimum_required(VERSION 3.10)
project(ChaCha20)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files from include/
include_directories(include)

# Collect all .cpp files from src/
file(GLOB SOURCES "src/*.cpp")

# Create executable from source files
add_executable(chacha20 ${SOURCES})
