cmake_minimum_required(VERSION 3.10)
project(EnigmaSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    #add_definitions(-DPDC_STATIC_BUILD)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ext/include")
    
    find_library(PDCURSES_LIB 
        NAMES pdcurses 
        PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libs" 
        NO_DEFAULT_PATH
    )

    set(CURSES_LIBRARIES ${PDCURSES_LIB})
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    set(CURSES_LIBRARIES ${CURSES_LIBRARIES})
endif()

add_executable(enigmasim 
    main.cpp
    enigma.cpp
    interface.cpp
    plugboard.cpp 
    rotor.cpp
    reflector.cpp
    handler.cpp
    tools.cpp
)

target_link_libraries(enigmasim PRIVATE ${CURSES_LIBRARIES})