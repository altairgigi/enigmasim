#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "handler.hpp"
#include "tools.hpp"
//function to load default settings
MachineConfig LoadDefaultSettings(std::string m) {
    if(m == "M3") {
        std::cout << "Loading standard model default settings.\n";
        return {PLUGBOARD_NOPLUGS, REFLECTOR_B, {ALPHABET, ROTOR_3, 0, 0}, {ALPHABET, ROTOR_2, 0, 0}, {ALPHABET, ROTOR_1, 0, 0}};
    }
    else {
        std::cout << "Loading default "<< m <<" settings.\n";
        return {PLUGBOARD_NOPLUGS, REFLECTOR_B_DUNN, {ALPHABET, ROTOR_3, 0, 0}, {ALPHABET, ROTOR_2, 0, 0}, {ALPHABET, ROTOR_1, 0, 0}, {ALPHABET, ROTOR_B, 0, 0}};
    }
}
//gets rotor settings through function to initialise struct
RotorConfig GetRotorSetting(std::string n, std::vector<int> &set) {
    std::string input; //this will be used to parse the input
    int conf, ring, offset; //these will be used to store the input parsed
    while(true) {
        if(n == "extra") {
            std::cout << "Select fourth rotor setting: \n";
        }
        else {
            std::cout << "Select " << n << " rotor setting: \n";
        }
        std::getline(std::cin, input);
        std::stringstream ss(input); //prepares the string to be parsed
        if (!(ss >> conf >> ring >> offset)) { //parse and validates the input 
            continue;
        }
        //ensures that if the value was already chosen the user is asked to input it again
        if(std::ranges::contains(set, conf)) //i chose std::range::contains over std::find because i only need a true/false result
        {
            std::cout << "Rotor already chosen once! All rotors are unique.\n";
            continue;
        }
        else{
            break;
        }
    }
    //if values are over range resets them
    ring = ring % 26;
    offset = offset %26;
    //if to handle variant configuration assignment
    if(n == "extra") {
        if(conf == 9) {
            return {ALPHABET, ROTOR_B, offset, ring};
        }
        else if(conf == 0) {
            return {ALPHABET, ROTOR_G, offset, ring};
        }
        else {
            std::cout << "Error: This configuration doesn't exists! Loading default rotor settings...\n";
            return {ALPHABET, ROTOR_B, 0, 0};
        }
    }
    else {
        if(conf >= 0 && conf <= 8) {
            set.push_back(conf);
        }
        //switch to handle standard configuration assignment
        switch(conf) {
            case 1: 
                return {ALPHABET, ROTOR_1, offset, ring};
                break;
            case 2:
                return {ALPHABET, ROTOR_2, offset, ring};
                break;
            case 3:
                return {ALPHABET, ROTOR_3, offset, ring};
                break;
            case 4:
                return {ALPHABET, ROTOR_4, offset, ring};
                break;
            case 5:
                return {ALPHABET, ROTOR_5, offset, ring};
                break;
            case 6:
                return {ALPHABET, ROTOR_6, offset, ring};
                break;
            case 7:
                return {ALPHABET, ROTOR_7, offset, ring};
                break;
            case 8:
                return {ALPHABET, ROTOR_8, offset, ring};
                break;
            default: //handles mistakes in configuration
                std::cout << "Error: This configuration doesn't exists! Loading default rotor settings...\n";
                if(n == "left") {
                    set.push_back(1);
                    return {ALPHABET, ROTOR_1, 0, 0};
                }
                else if(n == "middle") {
                    set.push_back(2);
                    return {ALPHABET, ROTOR_2, 0, 0};
                }
                else{
                    set.push_back(3);
                    return {ALPHABET, ROTOR_3, 0, 0};
                }
                break;
        }
    }
}
//function to get reflector settings
ReflectorConfig GetReflectorSetting() {
    char input;

    std::cout << "Select reflector: \n";
    std::cin >> input;
    std::cin.ignore(1000, '\n'); //cleans buffer

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
ReflectorConfig GetReflectorSetting(std::string mod) {
    char input;

    std::cout << "Select reflector: (i.e. 'B' or 'C')\n";
    std::cin >> input;
    std::cin.ignore(1000, '\n'); //cleans buffer

    if(std::tolower(input) == 'b') {
        return REFLECTOR_B_DUNN;
    }
    else if(std::tolower(input) == 'c') {
        return REFLECTOR_C_DUNN;
    }
    else {
        std::cout << "Error: Reflector initialisation failed! Loading default " << mod <<" setting...\n";
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
        std::cout << "Select plugs: \n";
        std::getline(std::cin, plugs);
        if(plugs.empty()) { //if the user just presses enter the plugboard configuration is skipped
            return plugCon;
        }
    }while(plugs.length() > 1 && plugs.length() %2 != 0); //checks if number of character is even

    for(int i = 0;  i < plugs.length() && i < 20; i++) { //manipulates data through indexes
        int c;
        if(i % 2 == 0) {
            c = std::toupper(plugs[i]) - 'A';
            plugCon.plugs[c] = std::toupper(plugs[i + 1]);
        }
        else {
            c = std::toupper(plugs[i]) - 'A';
            plugCon.plugs[c] = std::toupper(plugs[i - 1]);
        }
    }

    return plugCon;
}

//function to ask and load custom settings
MachineConfig LoadCustomSettings() {
    //these will hold the chosen setting to ensure they are selected only once
    std::vector<int> rotorSet, &set = rotorSet;

    std::cout << "This procedure will guide you through the setup.\n";

    //initialise components configurations via function to handle array decay and avoid repeating code
    std::cout << "Pick rotor configuration (1-8), then ring setting (0-25) and starting position (0-25).\n" 
              << "Es. '1 2 3' to use configuration I, with ring setting on 'c' and starting position on 'd'. Each rotor can be chosen only once.)\n";
    RotorConfig rotLeftCon = GetRotorSetting("left", set);
    RotorConfig rotMidCon = GetRotorSetting("middle", set);
    RotorConfig rotRightCon = GetRotorSetting("right", set);

    std::cout << "Use 'A', 'B', or 'C' to pick the reflector.\n";
    ReflectorConfig RefCon = GetReflectorSetting();

    std::cout << "Enter max 10 pairs of letters: es. 'azbuenlptv' to switch 'a' with 'z', 'b' with 'u', and so on. Press just Enter to skip.\n";
    PlugboardConfig plugCon = GetPlugboardSettings();
    //assembles configuration
    MachineConfig enigmaConfig = {plugCon, RefCon, rotLeftCon, rotMidCon, rotRightCon};

    return enigmaConfig;
}
//function to load custom settings for M4 model
MachineConfig LoadCustomSettings(std::string m) {
    //as above these will hold the chosen setting to ensure they are selected only once
    std::vector<int> rotorSettings, &settings = rotorSettings;

    std::cout << "This procedure will guide you through the setup.\n";
    
    //initialise components configurations via function to handle array decay and avoid repeating code
    std::cout << "Pick rotor configuration (1-8), then ring setting (0-25) and starting position (0-25).\n" 
              << "Es. '1 2 3' to use configuration I, with ring setting on 'c' and starting position on 'd'. Press Enter after each number.)\n";
    RotorConfig rotLeftCon = GetRotorSetting("left", settings);
    RotorConfig rotMidCon = GetRotorSetting("middle", settings);
    RotorConfig rotRightCon = GetRotorSetting("right", settings);

    std::cout << "Pick rotor configuration (9 or 0), then ring setting (0-25) and starting position (0-25).\n"
              << "Es. '9 2 3' to use configuration beta, with ring setting 'c' and starting position 'd'. Press Enter after each number\n";
    RotorConfig rotExtraCon = GetRotorSetting("extra", settings);

    std::cout << "Use 'A', 'B', or 'C' to pick the reflector.\n";
    ReflectorConfig RefCon = GetReflectorSetting(m);

    std::cout << "Enter max 10 pairs of letters: es. 'azbuenlptv' to switch 'a' with 'z', 'b' with 'u', and so on. Press just Enter to skip.\n";
    PlugboardConfig plugCon = GetPlugboardSettings();
    //assembles configuration
    MachineConfig enigmaConfig = {plugCon, RefCon, rotLeftCon, rotMidCon, rotRightCon, rotExtraCon};

    return enigmaConfig;
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