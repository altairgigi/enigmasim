#include <iostream>
#include <memory> //for the smart pointers
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
    char model{}, &m = model; //variables needed for initialisation
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
            m = '3';
        }
        else if(std::string(argv[2]) == "-m4"){
            MachineConfig enigmaConfig = LoadDefaultSettings("M4");
            machine = std::make_unique<EnigmaM4>(enigmaConfig);
            m = '4';
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
    if(argc == 1 || std::string(argv[1]) == "-info") {
        model = GetModel(); //model selection and setup
        if(model == '3') { //loads standard configuration
            MachineConfig enigmaConfig = LoadCustomSettings();
            machine = std::make_unique<Enigma>(enigmaConfig);
        }
        else{ //loads uboat configuration
            MachineConfig enigmaConfig = LoadCustomSettings("M4");
            machine = std::make_unique<EnigmaM4>(enigmaConfig);
        }
    }

    char key{}, lamp{}; //variables initialised to default value ('\0')
    char &k = key, &l = lamp; //alias for user input
    bool endEncrypt = false; //flag for the cycle
    std::vector<char> textInput, textOutput; //vectors where texts will be stored
    auto gui = std::make_unique<Interface>(); //interface class object

    //cycle for the encryption will prompt for a key, encrypt it and show the result
    while(!endEncrypt){
        gui->DrawUI(*machine, l, m);
        if((k = gui->GetInput(*machine, l, m)) == '\n'){ //checks if key pressed was enter, if not keeps encrypting
            endEncrypt = true; //if yes the flag gets true
            gui.reset();
            continue;
        }
        textInput.push_back(key); //saves key
        machine->Encrypt(k); //encrypts key
        textOutput.push_back(key); //saves encrypted key
        lamp = key;
        gui->DrawUI(*machine, l, m);
    }; //exits the cycle if the flag is true

    //ask if user wants to save to .txt
    if(std::toupper(ConfirmSave(textInput, textOutput)) == 'Y') {
        SaveFile(textOutput);
    }

    return 0;
}