cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(AirControl)

set(SOURCES
    src/Database.cpp
    src/Controller.cpp
    src/Airport.cpp
    src/Flight.cpp
    src/sources.cpp
)

add_executable(AirControl src/Database.cpp src/Controller.cpp src/Airport.cpp src/Flight.cpp src/source.cpp)