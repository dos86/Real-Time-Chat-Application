cmake_minimum_required(VERSION 3.10)
project(RealTimeChat)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Client.cpp
    src/Server.cpp
    src/Message.cpp
    src/Database.cpp
    main.cpp
)

# Executable
add_executable(RealTimeChat ${SOURCES})
