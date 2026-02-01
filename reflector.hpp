#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP
//include config.hpp for ReflectorConfig struct in constructor declaration
#include "config.hpp"
//declaration of reflector class
class Reflector {
    public:
        Reflector(ReflectorConfig reflectorCfg);
        void Reflect(int &index);
    private:
        char map[26];
};

#endif