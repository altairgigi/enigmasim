#include <iostream>
#include <memory> //for the smart pointer
#include <string> //for the arguments
#include <vector> //for the texts
#include "enigma.hpp"
#include "interface.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "config.hpp"
#include "handler.hpp"

int main (int argc, char *argv[]) {
    std::unique_ptr<Enigma> machine; //declare a smart pointer to avoid scope issue when initalising the machine
    //checks for the arguments 
    if(argc == 1){
        std::cout << "Welcome to EnigmaSim!\n";
    }
    else if(argc == 2 && std::string(argv[1]) == "-info") {
        PrintInstructions();
    }
    else if(argc == 3 && std::string(argv[1]) == "-skip") {
        if(std::string(argv[2]) == "-m3"){
            MachineConfig enigmaConfig = LoadDefaultSettings("M3");
            machine = std::make_unique<Enigma>(enigmaConfig);
        }
        else if(std::string(argv[2]) == "-m4"){
            MachineConfig enigmaConfig = LoadDefaultSettings("M4");
            machine = std::make_unique<EnigmaM4>(enigmaConfig);
        }
        else{
            PrintUsage(); //if the argument was correct but the option was not
            return 2;
        }
    }
    else{ //if arguments were entered incorrectly
        PrintUsage();
        return 1;
    }
    
    char key, choice, model; //user input and choices
    char &k = key; //alias for user input
    bool endEncrypt = false; //flag for the cycle
    std::vector<char> text, textEncrypted; //vectors where texts will be stored

    if(argc == 1 || std::string(argv[1]) == "-info") {
        model = GetModel(); //model selection and setup
        if(model == '1') { //loads standard configuration
            MachineConfig enigmaConfig = LoadCustomSettings();
            machine = std::make_unique<Enigma>(enigmaConfig);
        }
        else{ //loads uboat configuration
            MachineConfig enigmaConfig = LoadCustomSettings("M4");
            machine = std::make_unique<EnigmaM4>(enigmaConfig);
        }
    }

    PrintInterface(); //prints interface
    //cycle for the encryption will prompt for a key, encrypt it and show the result
    while(!endEncrypt){
        if((k = GetKey()) == 13){ //checks if key pressed was enter, if not keeps encrypting
            endEncrypt = true; //if yes the flag gets true
            continue;
        }
        text.push_back(key); //saves key
        machine->Encrypt(k); //encrypts key
        PrintInterface(); //prints interface
        LightKey(key); //shows encrypted key
        textEncrypted.push_back(key); //saves encrypted key
        PrintText(textEncrypted);
    }; //exits the cycle if the flag is true
    std::cout << "Your text: \n";
    PrintText(text);
    std::cout << "Your encrypted text: \n";
    PrintText(textEncrypted); //prints final text
    //asks if the user wants to save the encrypted text
    std::cout << "Do you want to save your encrypted text? (y/n)\n";
    std::cin >> choice;
    if(choice == 'y' || choice == 'Y') {
        SaveFile(textEncrypted);
    }

    return 0;
}