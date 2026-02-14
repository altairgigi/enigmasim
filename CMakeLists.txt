cmake_minimum_required(VERSION 3.10)
project(EnigmaSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    
    find_library(PDCURSES_LIB 
        NAMES pdcurses 
        PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ext/libs" 
        NO_DEFAULT_PATH
    )

    set(CURSES_LIBRARIES ${PDCURSES_LIB})
    set(EXTERNAL_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/ext/include")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    set(CURSES_LIBRARIES ${CURSES_LIBRARIES})
endif()

add_executable(enigmasim 
    source/main.cpp
    source/enigma.cpp
    source/interface.cpp
    source/plugboard.cpp 
    source/rotor.cpp
    source/reflector.cpp
    source/handler.cpp
    source/tools.cpp
)

target_include_directories(enigmasim PRIVATE 
    include
    ${EXTERNAL_INCLUDE}
)

target_link_libraries(enigmasim PRIVATE ${CURSES_LIBRARIES})

target_compile_options(enigmasim PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall>
)