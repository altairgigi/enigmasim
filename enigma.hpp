#ifndef ENIGMA_HPP
#define ENIGMA_HPP
//include all the necessary components headers
#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"
//declaration of the enigma class
class Enigma{
public:
    Enigma(MachineConfig enigma);
    virtual ~Enigma(); //as a rule if at least function is virtual then is good practice to have a virtual destructor
    virtual void Encrypt(char &key); //the child class will override it
    void StepRotors();
protected:
    Rotor rotorLeft;
    Rotor rotorMiddle;
    Rotor rotorRight;
    Reflector reflex;
    Plugboard board;
};
//declaration of the child enigma M4 class
class EnigmaM4 : public Enigma {
public:
    EnigmaM4(MachineConfig enigma);
    ~EnigmaM4();
    void Encrypt(char &key) override; //overrides the encryption function; StepRotors is left untouched because the fourth rotor doesn't rotate
private:
    Rotor rotorExtra;
};

#endif