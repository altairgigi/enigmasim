#include <iostream>
#include <vector>
#include "enigma.hpp"
#include "interface.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "config.hpp"
#include "files.hpp"

int main () {
    char key; //user input
    char &k = key; //alias for user input
    char plugboardConfig[26] = PLUGBOARD_NOPLUGS, reflectorConfig[26] = REFLECTOR_B; //configurations for reflector and plugboard are arrays
    RotorConfig rotorLeftConfig = ROTOR_1, rotorCentreConfig = ROTOR_2, rotorRightConfig = ROTOR_3; //configuration for rotors is a struct
    bool endEncrypt = false; //flag for the cycle
    std::vector<char> text, textEncrypted; //vectors where texts will be stored

    PrintInstructions(); //instructions for use
    Enigma machine{plugboardConfig, rotorLeftConfig, rotorCentreConfig, rotorRightConfig, reflectorConfig};
    PrintInterface(); //prints interface
    
    while(!endEncrypt){
        if((k = GetKey()) == 13){ //checks if key pressed was enter, if not keeps encrypting
            endEncrypt = true; //if yes the flag gets true
            continue;
        }
        text.push_back(key); //saves key
        machine.Encrypt(k); //encrypts key
        PrintKey(key); //shows encrypted key
        textEncrypted.push_back(key); //saves encrypted key
    }; //exits the cycle if the flag is true
    std::cout << "Your text: \n";
    PrintText(text);
    std::cout << "Your encrypted text: \n";
    PrintText(textEncrypted); //prints final text

    return 0;
}