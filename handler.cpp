#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>
#include <format>
#include "handler.hpp"
#include "config.hpp"
//function to load default settings
MachineConfig LoadDefaultSettings(std::string m) {
    if(m == "M3") {
        std::cout << "Loading standard model default settings.\n";
        return {PLUGBOARD_NOPLUGS, REFLECTOR_B, ROTOR_3, ROTOR_2, ROTOR_1};
    }
    else {
        std::cout << "Loading default "<< m <<" settings.\n";
        return {PLUGBOARD_NOPLUGS, REFLECTOR_B_DUNN, ROTOR_3, ROTOR_2, ROTOR_1, ROTOR_B};
    }
}
//gets rotor settings through function to initialise struct
RotorConfig GetRotorSetting(std::string n) {
    int select;
    if(n == "extra") {
        std::cout << "Select fourth rotor: \n"
                  << "(Pick either 9 or 0, then ring setting and starting positiones. Es. '923' to use configuration beta, with ring setting 2 and starting position 3.)\n";
    }
    else {
        std::cout << "Select "<< n << " rotor: \n"
                  << "(Pick 1-8, then ring setting and starting position. Es. '123' to use configuration I, with ring setting 2 and starting position 3.)\n";
    }
    std::cin >> select;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //cleans buffer
    //if to handle variant configuration assignment
    if(n == "extra") {
        if(select == 9) {
            return ROTOR_B;
        }
        else if(select == 0) {
            return ROTOR_G;
        }
        else {
            std::cout << "Error: This configuration doesn't exists! Loading default rotor settings...\n";
            return ROTOR_B;
        }
    }
    //switch to handle standard configuration assignment
    switch(select) {
        case 1: 
            return ROTOR_1;
            break;
        case 2:
            return ROTOR_2;
            break;
        case 3:
            return ROTOR_3;
            break;
        case 4:
            return ROTOR_4;
            break;
        case 5:
            return ROTOR_5;
            break;
        case 6:
            return ROTOR_6;
            break;
        case 7:
            return ROTOR_7;
            break;
        case 8:
            return ROTOR_8;
            break;
        default: //handles mistakes in configuration
            std::cout << "Error: This configuration doesn't exists! Loading default rotor settings...\n";
            if(n == "left") {
                return ROTOR_3; //{ALPHABET, ROTOR_3, select[2]};
            }
            else if(n == "middle") {
                return ROTOR_2; //{ALPHABET, ROTOR_2, select[2]};
            }
            else{
                return ROTOR_1; //{ALPHABET, ROTOR_1, select[2]};
            }
            break;
    }
}
//function to get reflector settings
ReflectorConfig GetReflectorSetting() {
    char input;

    std::cout << "Select reflector: (i.e. 'A', 'B', or 'C')\n";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //cleans buffer

    if(std::tolower(input) == 'a') {
        return REFLECTOR_A;
    }
    else if(std::tolower(input) == 'b') {
        return REFLECTOR_B;
    }
    else if(std::tolower(input) == 'c') {
        return REFLECTOR_C;
    }
    else {
        std::cout << "Error: Reflector initialisation failed! Loading default standard setting...\n";
        return REFLECTOR_B;
    }
}
//function to get reflector settings for the variant model
ReflectorConfig GetReflectorSetting(std::string m) {
    char input;

    std::cout << "Select reflector: (i.e. 'B' or 'C')\n";
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //cleans buffer

    if(std::tolower(input) == 'b') {
        return REFLECTOR_B_DUNN;
    }
    else if(std::tolower(input) == 'c') {
        return REFLECTOR_C_DUNN;
    }
    else {
        std::cout << "Error: Reflector initialisation failed! Loading default " << m <<" setting...\n";
        return REFLECTOR_B_DUNN;
    }
}
//function to get the plugs settings
PlugboardConfig GetPlugboardSettings() {
    std::string plugs;
    PlugboardConfig plugCon = {PLUGBOARD_NOPLUGS}; //initialises config to a default value for later manipulation

    do{
        if(plugs.length() > 1 && plugs.length() %2 != 0) { //this won't run during first cycle
            std::cout << "Attention! You entered an odd number of plugs!\n";
        }
        std::cout << "Select plugs: (Enter max 5 pairs of letters: es. 'az' to switch 'a' with 'z'. Press just Enter to skip.)\n";
        std::getline(std::cin, plugs);
        if(plugs.empty()) { //if the user just presses enter the plugboard configuration is skipped
            return plugCon;
        }
    }while(plugs.length() > 1 && plugs.length() %2 != 0); //checks if number of character is even

    for(int i = 0;  i < plugs.length() && i < 10; i++) { //manipulated data through indexes
        int c;
        if(i % 2 != 0) {
            c = std::toupper(plugs[i]) - 'A';
            plugCon.plugs[c] = plugs[i + 1];
        }
        else {
            c = std::toupper(plugs[i]) - 'A';
            plugCon.plugs[c] = plugs[i - 1];
        }
    }

    return plugCon;
}

//function to ask and load custom settings
MachineConfig LoadCustomSettings() {
    std::cout << "This procedure will guide you through the setup.\n";
    //initialise components configurations via function to handle array decay and avoid repeating code
    RotorConfig rotLeftCon = GetRotorSetting("left");
    RotorConfig rotMidCon = GetRotorSetting("middle");
    RotorConfig rotRightCon = GetRotorSetting("right");
    ReflectorConfig RefCon = GetReflectorSetting();
    PlugboardConfig plugCon = GetPlugboardSettings();
    //assembles configuration
    MachineConfig enigmaConfig = {plugCon, RefCon, rotLeftCon, rotMidCon, rotRightCon};

    return enigmaConfig;
}
//function to load custom settings for M4 model
MachineConfig LoadCustomSettings(std::string m) {
    std::cout << "This procedure will guide you through the setup.\n";
    //initialise components configurations via function to handle array decay and avoid repeating code
    RotorConfig rotLeftCon = GetRotorSetting("left");
    RotorConfig rotMidCon = GetRotorSetting("middle");
    RotorConfig rotRightCon = GetRotorSetting("right");
    RotorConfig rotExtraCon = GetRotorSetting("extra");
    ReflectorConfig RefCon = GetReflectorSetting(m);
    PlugboardConfig plugCon = GetPlugboardSettings();
    //assembles configuration
    MachineConfig enigmaConfig = {plugCon, RefCon, rotLeftCon, rotMidCon, rotRightCon, rotExtraCon};

    return enigmaConfig;
}
//function to get date and time and format them
std::string GetDateAndTime() {
    auto time = std::chrono::system_clock::now(); //let the compile handle type definition for the result of now();
    return std::format("{:%d-%m-%Y-%H:%M}", time); //converts the mow() result in human readable format
}
//function to save text as file with append
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