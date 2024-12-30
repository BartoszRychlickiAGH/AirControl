cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(AirControl)

set(SOURCES
    src/Database.cpp
    src/IDatabase.hpp
    src/Database.hpp
    src/Controller.cpp
    src/IController.hpp
    src/Controller.hpp
    src/Airport.cpp
    src/IAirport.hpp
    src/Airport.hpp
    src/Flight.cpp
    src/IFlight.hpp
    src/Flight.hpp
    src/source.cpp
    src/IController_Airport.hpp
)

add_executable(AirControl ${SOURCES})