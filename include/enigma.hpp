#ifndef ENIGMA_HPP
#define ENIGMA_HPP

//include all the necessary components headers
#include <vector>
#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"

//declaration of the enigma class
class Enigma{
public:
    Enigma(MachineConfig enigma);
    virtual ~Enigma(); //as a rule if at least function is virtual then is good practice to have a virtual destructor
    virtual void Encrypt(char &key); //the child class will override it
    void StepRotors(); //function to orchestrate the rotors rotation
    virtual std::vector<char> GetRotorsPos() const; //function to get the rotors position
protected:
    Plugboard board;
    Reflector reflex;
    Rotor rotorLeft;
    Rotor rotorMiddle;
    Rotor rotorRight;
};

//declaration of the child enigma M4 class
class EnigmaM4 : public Enigma {
public:
    EnigmaM4(MachineConfig enigma);
    ~EnigmaM4();
    void Encrypt(char &key) override; //overrides the encryption function; StepRotors is left untouched because the fourth rotor doesn't rotate
    std::vector<char> GetRotorsPos() const override;
private:
    Rotor rotorExtra;
};

#endif