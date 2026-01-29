# EnigmaSim

EnigmaSim is an historically accurate Enigma machine simulator made in C++ (c++23).

## Installation

Download the 'enigmasim' file on your Linux system or the 'enigmasim.exe' file on Windows from the Release section.

## Purpose
EnigmaSim is a project which aimed at creating a working and historically accurate Enigma machine simulator while mastering a number C++ features and techniques.
As consequence it required to 1) understand how the Enigma worked and encrypted data and 2) how to translate its function to C++ while ensuring code readability and historical accuracy.
In order to do so, EnigmaSim employs all the basic features of C++ (control flow, arrays, vectors, classes, structs, files, pointers, etc) and the four pillars of OOP.

## Features
EnigmaSim is intended to be fully fledged simulator and as such it has:
* complete and accurate encryption system;
* two different kinds of historical models (M3 and M4);
* full set of rotors (I-VIII + beta and gamma) and reflectors (A, B, and C and 'thin' variants) just like the ones used between 1930 and 1945;
* clean and simple CLI with working lamps and rotors in ASCII art; **WIP**
* simulation of 'double step' anomaly, ringastellung, grundstellung, etc;
* user defined settings (machine model, rotors, reflectors and plugboard) via arguments; **WIP**
* file saving system (as .txt). **WIP**

## License

[GPL3.0](https://choosealicense.com/licenses/gpl-3.0/)