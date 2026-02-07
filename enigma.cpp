#include <iostream>
#include "enigma.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "config.hpp"
#include "tools.hpp"
//class enigma constructor
Enigma::Enigma(MachineConfig eni)
: board(eni.plugboardConfig), rotorLeft(eni.rotorLeftConfig), rotorMiddle(eni.rotorMiddleConfig), rotorRight(eni.rotorRightConfig), reflex(eni.reflectorConfig) {
}
//class enigma constructor with logging
Enigma::~Enigma() {
    std::cout << "Enigma machine deactivated. Take note and rest.\n";
}
//function to encrypt 
void Enigma::Encrypt(char &key) {
    int index = Ctoi(key); //set to be the array position of variable 'k' to handle the mapping
    int &i = index;
    StepRotors(); //first steps the rotors then proceed with the sequence
    board.Swap(key, i);
    rotorRight.ShiftForward(i);
    rotorMiddle.ShiftForward(i);
    rotorLeft.ShiftForward(i);
    reflex.Reflect(i);
    rotorLeft.ShiftBackward(i);
    rotorMiddle.ShiftBackward(i);
    rotorRight.ShiftBackward(i);
    board.Swap(key, i);
}
//function to orchestrate rotors rotation
void Enigma::StepRotors() {
    rotorRight.Rotate();
    if(rotorRight.IsOnNotch()) {
        rotorMiddle.Rotate();
        if(rotorMiddle.IsOnNotch())
        {
            rotorLeft.Rotate();
        }
    }
    else if(rotorMiddle.IsOnNotch()) {
        rotorMiddle.Rotate(); //this simulates the 'double step' anomaly
        rotorLeft.Rotate();
    }
}
//function to get all the rotors positions
std::vector<char> Enigma::GetRotorsPos() const {
    return {rotorLeft.GetPos(), rotorMiddle.GetPos(), rotorRight.GetPos()};
}
//derived class enigma M4 constructor
EnigmaM4::EnigmaM4(MachineConfig eni)
: Enigma(eni), rotorExtra(eni.rotorExtraConfig) {
}
//derived class enigma M4 destructor
EnigmaM4::~EnigmaM4() {}
//derived class function to encrypt 
void EnigmaM4::Encrypt(char &key) {
    int index = Ctoi(key);
    int &i = index;
    StepRotors();
    board.Swap(key, i); //sequence is the same except for the fourth rotor right before and right after the reflector
    rotorRight.ShiftForward(i);
    rotorMiddle.ShiftForward(i);
    rotorLeft.ShiftForward(i);
    rotorExtra.ShiftForward(i);
    reflex.Reflect(i);
    rotorExtra.ShiftBackward(i);
    rotorLeft.ShiftBackward(i);
    rotorMiddle.ShiftBackward(i);
    rotorRight.ShiftBackward(i);
    board.Swap(key, i);
}
//function to get all the M4 rotors positions
std::vector<char> EnigmaM4::GetRotorsPos() const {
    return {rotorLeft.GetPos(), rotorMiddle.GetPos(), rotorRight.GetPos(), rotorExtra.GetPos()};
}