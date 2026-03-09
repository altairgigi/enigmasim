# EnigmaSim
![C++](https://img.shields.io/badge/C++-23-blue.svg)
![ncurses](https://img.shields.io/badge/UI-ncurses-000000?style=flat&logo=gnuterminal&logoColor=green)
![Build](https://img.shields.io/badge/Build-CMake-064F8C?style=flat&logo=cmake)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)

EnigmaSim is an historically accurate Enigma machine simulator made in C++ (c++23).

![Enigma simulator demo](./assets/enigmademo.gif)

## Installation
Download the `enigmasim` file on your Linux system or the `enigmasim.exe` file on Windows from the Release section.

## Requirements
If you want to compile the program by yourself you'll need either `PDCurses` (on Windows) or `Ncurses` (on Linux).

## How to use
Launch the `enigmasim` executable by command or double-click to launch the program normally.

If you want to have more options, launch from terminal and use arguments and options:

| Argument | Result | Option (after -skip) | Result |
|---|---|---|---|
| -info | Shows informations on the machine and the setup procedure. | -m3 | Loads default configuration for the standard M3 model (rotors III-II-I with base position 'A' and ring setting 'A', reflector 'B', and no plugs inserted). |
| -skip | Skips setup and loads default configuration depending on option selected. | -m4 | Loads default configuration for the uboat M4 model (rotors 'beta-III-II-I' with base position 'A' and ring setting 'A', reflector 'B thin', and no plugs inserted). |

## Purpose
EnigmaSim is a project which aimed at creating a working, historically accurate and mechanically faithful Enigma machine simulator while mastering a number C++ features and techniques.
As consequence it required to 1) understand how the Enigma worked and encrypted data and 2) how to translate its function to C++ while ensuring DRY code, readability and historical accuracy.

The main objective, and obstacle, was to simulate the actual mechanical and electrical behaviour of the machine. Therefore, to handle the components' configurations, were not used standard C++ library strings or vectors but rather classic "C-style" arrays and to handle the transformation of the signal were not used mathematical formulas but actual 'mechanical' simulation.

## Tech Stack

### Core Engine

**Language Standard**: C++23 

**Platforms**: Windows & Linux

**Build**: CMake

### Logic & Memory Management

**Smart Pointers**: Initialization via `std::unique_ptr` to ensures no memory leaks and safe memory management in the heap.

**C-Style Arrays**: Used for low-level mechanical simulation of rotors to maximize access performance.

**Vectors & Strings**: Dynamic management of user configurations and encryptions and use of `algorithm` to copy configurations.

**Structs**: Definitions of rigorous data structures for passing configuration parameters between machine components.

**Explicit Casting**: Use of `static_cast` for conversion between char and int (es. mapping of rotor indexes and configurations).

### Object-Oriented Programming

The project is built on an object-oriented architecture that mirrors the mechanical behaviour of the machine:

**Abstraction & Encapsulation**: Each component is isolated; the internal state of the rotors is protected and accessible only through defined interfaces.

**Inheritance & Polymorphism**: Implementation of a class hierarchy for the different machine models, with method overrides behaviors and functions.

### Interface & Interaction

**TUI Graphics**: Developed with the `ncurses` library.

**CLI Setup**: Command-line setup wizard and argument management for quick access to help functions or bypassing the setup.

**File Management**: Persistence system for saving encryption logs to file with timestamps via `chrono` and `format`.

## Features
EnigmaSim is intended to be fully fledged simulator and as such it has:
* complete and accurate encryption system with faithful mechanical/electrical behaviour simulation;
* two different kinds of historical models (M3 and M4) plus countless setting combinations;
* full set of rotors (I-VIII and beta and gamma) and reflectors (A, B, and C and 'thin' variants) just like the ones used between 1930 and 1945;
* simulation of 'double step' anomaly, ringstellung, grundstellung, etc;
* user-defined settings (machine model, rotors, reflectors and plugboard settings) via CLI guided setup;
* clean and simple text-based GUI with working lamps and rotors;
* file saving system (as .txt).

## License
[GPL3.0](https://choosealicense.com/licenses/gpl-3.0/)