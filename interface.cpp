#include <iostream>
#include <conio.h> //will work only on windows
#include <vector>
#include "interface.hpp"
//function to print instructions on how the simulator will work
void PrintInstructions() {
    std::cout << "This is any Enigma Simulator, any key you press will be encrypted.\n";
}
//function to print the interface
void PrintInterface() {
    std::cout << "Interface placeholder!\n";
}
//function to get the input key
char GetKey() {
    char key;
    std::cout << "Press any key:\n";
    key = _getch();
    if(islower(key)) { //check if letter is lowercase
        key = toupper(key); //converts to uppercase
    }
    return key;
}
//function to print the key once the input is taken
void PrintKey(char key) {
    std::cout << "Lamp lit: " << key << "\n";
}
//function to print the before or text after the encryption
void PrintText(std::vector<char> text) {
    for(char c : text){
        std::cout << c;
    }
    std::cout << "\n";
}