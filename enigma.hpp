#ifndef ENIGMA_HPP
#define ENIGMA_HPP
//include all the necessary components headers
#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"
//declaration of the enigma class
class Enigma{
public:
    Enigma(char plugWiring[], RotorConfig left, RotorConfig centre, RotorConfig right, char reflectorCfg[]);
    ~Enigma();
    void Encrypt(char &key);
    void StepRotors();
private:
    Rotor rotorLeft;
    Rotor rotorCentre;
    Rotor rotorRight;
    Reflector reflex;
    Plugboard board;
};

#endif