#include <iostream>
#include <fstream>
#include <chrono>
#include <format>
#include "handler.hpp"
#include "config.hpp"

std::string GetDateAndTime() {
    auto time = std::chrono::system_clock::now(); //let the compile handle type definition for the result of now();
    return std::format("{:%d-%m-%Y-%H:%M}", time); //converts the mow() result in human readable format
}

void SaveFile(std::vector<char> txt) {
    std::ofstream opfile("output.txt", std::ios::app); //will use the file to record every past encoding
    //check if file successfully opened
    if(opfile.is_open()) {
        for(int i = 1; i <= txt.size(); i++) {
            opfile << txt[i-1];
            if(i % 4 == 0) { //enigma encrytions were recorded as groups of four letters
                opfile << " ";
            }
        }
        opfile << "\t" << GetDateAndTime() <<"\n"; //append the date and time of the encryption
        std::cout << "Encryption saved.\n";
    }
    else { //if creation or opening failed prints error
        std::cout << "Error: File creation or opening failed!";
    }
    opfile.close(); //always close the file after
}