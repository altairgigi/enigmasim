#include <iostream>
#include <memory>
#include <vector>
#include "enigma.hpp"
#include "interface.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "config.hpp"

int main () {
    char key, model; //user input and model
    char &k = key; //alias for user input
    char plugboardConfig[26] = PLUGBOARD_NOPLUGS; //configuration for reflector and plugboard are arrays
    RotorConfig rotorLeftConfig = ROTOR_3, rotorMiddleConfig = ROTOR_2, rotorRightConfig = ROTOR_1, rotorExtraConfig = ROTOR_B; //configurations for rotors is a struct
    bool endEncrypt = false; //flag for the cycle
    std::vector<char> text, textEncrypted; //vectors where texts will be stored
    std::unique_ptr<Enigma> machine; //declare a smart pointer to avoid scope issue when initalising the machine

    model = PrintInstructions(); //instructions for use and model selection
    if(model == '1') { //loads standard configuration
        char reflectorConfig[26] = REFLECTOR_B; 
        machine = std::make_unique<Enigma>(plugboardConfig, rotorLeftConfig, rotorMiddleConfig, rotorRightConfig, reflectorConfig);
    }
    else if(model == '2') { //loads uboat configuration
        char reflectorConfig[26] = REFLECTOR_B_DUNN; 
        machine = std::make_unique<EnigmaM4>(rotorExtraConfig, plugboardConfig, rotorLeftConfig, rotorMiddleConfig, rotorRightConfig, reflectorConfig);
    }
    else { //prints error and exits
        std::cout << "Error: Invalid choice! Exiting program!\n";
        return 1;
    }
    PrintInterface(); //prints interface
    
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

    return 0;
}