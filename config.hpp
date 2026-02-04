#pragma once //prefer this since struct can be defined only once in a single compilation
//struct for components configuration to handle array decay; std::array not used for the sake of simplicity
//struct for plugboard configuration
struct PlugboardConfig {
    char plugs[26];
};
//struct to save rotor configuration
struct RotorConfig {
    char ring[26];
    char root[26];
    char notchA;
    char notchB; //only configurations VI, VII, VIII will use this
    int offset;
    int ringSetting;
};
//struct for reflector configuration
struct ReflectorConfig {
    char map[26];
};
//struct to save enigma machine config
struct MachineConfig {
    PlugboardConfig plugboardConfig;
    ReflectorConfig reflectorConfig;
    RotorConfig rotorLeftConfig, rotorMiddleConfig, rotorRightConfig, rotorExtraConfig;
};
//to be used as reference for rotor ring, plugboard when there are no plugs and reflector when missing
#define ALPHABET {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
//may use a default configuration
#define PLUGBOARD_NOPLUGS ALPHABET
#define PLUGBOARD_DEFAULT {'Z', 'B', 'X', 'D', 'V', 'F', 'H', 'G', 'I', 'K', 'J', 'L', 'N', 'M', 'O', 'Q', 'P', 'R', 'T', 'S', 'U', 'E', 'W', 'C', 'Y', 'A'} //az, cx, ev, hg, jk, mn, pq, st
//configurations for rotors, the notch will be set in letter after for the check (es. configuration I historically had notch on 'q' but the check will be on the 'r')
#define ROTOR_1 {'E', 'K', 'M', 'F', 'L', 'G', 'D', 'Q', 'V', 'Z', 'N', 'T', 'O', 'W', 'Y', 'H', 'X', 'U', 'S', 'P', 'A', 'I', 'B', 'R', 'C', 'J'}, 'R', '\0'
#define ROTOR_2 {'A', 'J', 'D', 'K', 'S', 'I', 'R', 'U', 'X', 'B', 'L', 'H', 'W', 'T', 'M', 'C', 'Q', 'G', 'Z', 'N', 'P', 'Y', 'F', 'V', 'O', 'E'}, 'F', '\0'
#define ROTOR_3 {'B', 'D', 'F', 'H', 'J', 'L', 'C', 'P', 'R', 'T', 'X', 'V', 'Z', 'N', 'Y', 'E', 'I', 'W', 'G', 'A', 'K', 'M', 'U', 'S', 'Q', 'O'}, 'W', '\0'
#define ROTOR_4 {'E', 'S', 'O', 'V', 'P', 'Z', 'J', 'A', 'Y', 'Q', 'U', 'I', 'R', 'H', 'X', 'L', 'N', 'F', 'T', 'G', 'K', 'D', 'C', 'M', 'W', 'B'}, 'K', '\0' //herr
#define ROTOR_5 {'V', 'Z', 'B', 'R', 'G', 'I', 'T', 'Y', 'U', 'P', 'S', 'D', 'N', 'H', 'L', 'X', 'A', 'W', 'M', 'J', 'Q', 'O', 'F', 'E', 'C', 'K'}, 'A', '\0' //herr
#define ROTOR_6 {'J', 'P', 'G', 'V', 'O', 'U', 'M', 'F', 'Y', 'Q', 'B', 'E', 'N', 'H', 'Z', 'R', 'D', 'K', 'A', 'S', 'X', 'L', 'I', 'C', 'T', 'W'}, 'A', 'N' //kriegsmarine
#define ROTOR_7 {'N', 'Z', 'J', 'H', 'G', 'R', 'C', 'X', 'M', 'Y', 'S', 'W', 'B', 'O', 'U', 'F', 'A', 'I', 'V', 'L', 'P', 'E', 'K', 'Q', 'D', 'T'}, 'A', 'N' //kriegsmarine
#define ROTOR_8 {'F', 'K', 'Q', 'H', 'T', 'L', 'X', 'O', 'C', 'B', 'J', 'S', 'P', 'D', 'Z', 'R', 'A', 'M', 'E', 'W', 'N', 'I', 'U', 'Y', 'G', 'V'}, 'A', 'N' //kreigsmarine
#define ROTOR_B {'L', 'E', 'Y', 'J', 'V', 'C', 'N', 'I', 'X', 'W', 'P', 'B', 'Q', 'M', 'D', 'R', 'T', 'A', 'K', 'Z', 'G', 'F', 'U', 'H', 'O', 'S'}, '\0', '\0' //M4 only
#define ROTOR_G {'F', 'S', 'O', 'K', 'A', 'N', 'U', 'E', 'R', 'H', 'M', 'B', 'T', 'I', 'Y', 'C', 'W', 'L', 'Q', 'P', 'Z', 'X', 'V', 'G', 'J', 'D'}, '\0', '\0' //M4 only
//configurations for the reflector
#define REFLECTOR_NONE ALPHABET
#define REFLECTOR_A {'E', 'J', 'M', 'Z', 'A', 'L', 'Y', 'X', 'V', 'B', 'W', 'F', 'C', 'R', 'Q', 'U', 'O', 'N', 'T', 'S', 'P', 'I', 'K', 'H', 'G', 'D'}
#define REFLECTOR_B {'Y', 'R', 'U', 'H', 'Q', 'S', 'L', 'D', 'P', 'X', 'N', 'G', 'O', 'K', 'M', 'I', 'E', 'B', 'F', 'Z', 'C', 'W', 'V', 'J', 'A', 'T'}
#define REFLECTOR_C {'F', 'V', 'P', 'J', 'I', 'A', 'O', 'Y', 'E', 'D', 'R', 'Z', 'X', 'W', 'G', 'C', 'T', 'K', 'U', 'Q', 'S', 'B', 'N', 'M', 'H', 'L'}
#define REFLECTOR_B_DUNN {'E', 'N', 'K', 'Q', 'A', 'U', 'Y', 'W', 'J', 'I', 'C', 'O', 'P', 'B', 'L', 'M', 'D', 'X', 'Z', 'V', 'F', 'T', 'H', 'R', 'G', 'S'} //M4 only
#define REFLECTOR_C_DUNN {'R', 'D', 'O', 'B', 'J', 'N', 'T', 'K', 'V', 'E', 'H', 'M', 'L', 'F', 'C', 'W', 'Z', 'A', 'X', 'G', 'Y', 'I', 'P', 'S', 'U', 'Q'} //M4 only