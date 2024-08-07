cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Collect all .cpp files in src/ and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the main executable using all the collected sources
add_executable(${PROJECT_NAME} ${SOURCES})