#include <chrono>
#include <format>
#include "tools.hpp"

//converts alphabet letter into number
int Ctoi(char c) {
   return static_cast<int>(c - 'A');
}

//converts number into alphabet letter
char Itoc(int i) {
    return static_cast<char>('A' + i);
}

//function to get date and time and format them
std::string GetDateAndTime() {
    auto time = std::chrono::system_clock::now(); //let the compile handle type definition for the result of now();
    return std::format("{:%d-%m-%Y-%H:%M}", time); //converts the mow() result in human readable format
}