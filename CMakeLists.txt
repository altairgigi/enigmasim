cmake_minimum_required(VERSION 3.10)

project(EnigmaMachine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(enigmasim 
    main.cpp
    enigma.cpp
    interface.cpp
    plugboard.cpp 
    rotor.cpp
    reflector.cpp
    handler.cpp
)