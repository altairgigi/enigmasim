#include <iostream>
#include <conio.h> //will work only on windows
#include <vector>
#include "interface.hpp"
//function to print instructions on how the simulator will work
char PrintInstructions() {
    char m;
    std::cout << "Welcome to EnigmaSim! This is a simple yet historically accurate Enigma machine simulator.\n"
              << "\nOperators who were tasked with managing the machine had to follow a strict sequence of operations:\n"
              << "1) Consult  the cipher for that day;\n"
              << "2) Take the three rotors to be used;\n"
              << "3) Set the programming of each individual rotor to the triplet of letters indicated (Ringstellung);\n"
              << "4) Insert them into the machine in the indicated order (Walzenlage);\n"
              << "5) Adjust the initial position of the rotor rings to the triplet of letters indicated (Grundstellung);\n"
              << "6) Configure the letter exchange pins as determined by the Enigma key for that day (Steckerverbindungen).\n"
              << "\nLuckily, you will just input letters and get the encrypted result.\nSelect the model you want to use: '1' for M3 (Standard) and '2' for M4 (Uboat)\n";
    std::cin >> m;
    return m;
}
//function to print the interface
void PrintInterface() {
    std::cout << "\033[2J\033[H"; //ansi escape sequence to clear the screen
    std::cout << "       >[A]>[A]>[A]        \n\n"
              << "(Q)(W)(E)(R)(T)(Z)(U)(I)(O)\n"
              << " (A)(S)(D)(F)(G)(H)(J)(K)  \n"
              << "(P)(Y)(X)(C)(V)(B)(N)(M)(L)\n";
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
void LightKey(char key) {
    std::cout << "Lamp lit: " << key << "\n";
}
//function to print the before or text after the encryption
void PrintText(std::vector<char> text) {
    for(int i = 1; i <= text.size(); i++){ //count starts from 1 to handle % 4
        std::cout << text[i-1];
        if(i % 4 == 0) { //original enigma encrypted text was recorded in groups of four letters
            std::cout << " ";
        }
    }
    std::cout << "\n";
}