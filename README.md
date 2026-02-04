# EnigmaSim

EnigmaSim is an historically accurate Enigma machine simulator made in C++ (c++23).

## Installation

Download the 'enigmasim' file on your Linux system or the 'enigmasim.exe' file on Windows from the Release section.

## Purpose
EnigmaSim is a project which aimed at creating a working, historically accurate and mechanically faithful Enigma machine simulator while mastering a number C++ features and techniques.
As consequence it required to 1) understand how the Enigma worked and encrypted data and 2) how to translate its function to C++ while ensuring DRY code, readability and historical accuracy.
The main objective, and obstacle, was to simulate the actual mechanical and electrical behaviour of the machine. Therefore, to handle the components' configurations, were not used standard C++ library strings or vectors but rather classic "C-style" arrays.
EnigmaSim employs all the basic features of C++ (control flow, strings, vectors, classes, structs, file management, pointers, etc) and the 'four pillars' of OOP.

## Features
EnigmaSim is intended to be fully fledged simulator and as such it has:
* complete and accurate encryption system with faithful mechanical/electrical behaviour simulation;
* two different kinds of historical models (M3 and M4);
* full set of rotors (I-VIII + beta and gamma) and reflectors (A, B, and C and 'thin' variants) just like the ones used between 1930 and 1945;
* clean and simple TUI with working lamps and rotors; **WIP**
* simulation of 'double step' anomaly, ringstellung, grundstellung, etc;
* user-defined settings (machine model, rotors, reflectors and plugboard settings) via CLI guided setup;
* file saving system (as .txt).

## License

[GPL3.0](https://choosealicense.com/licenses/gpl-3.0/)