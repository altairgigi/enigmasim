#include <chrono>
#include <format>
#include "tools.hpp"

//converts number into alphabet letter
int Ctoi(char c) {
   return c - 'A';
}

//converts alphabet letter into number
char Itoc(int i) {
    return 'A' + i;
}

//function to get date and time and format them
std::string GetDateAndTime() {
    auto time = std::chrono::system_clock::now(); //let the compile handle type definition for the result of now();
    return std::format("{:%d-%m-%Y-%H:%M}", time); //converts the mow() result in human readable format
}