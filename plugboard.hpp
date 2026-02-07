#ifndef PLUGBOARD_HPP
#define PLUGBOARD_HPP

//include config.hpp for PlugboardConfig struct in constructor declaration
#include "config.hpp"

//declaration of the plugboard class
class Plugboard {
    public:
        Plugboard(PlugboardConfig plugboardCfg);
        void Swap(char &key, int &index);
    private:
        char plugs[26];
};

#endif