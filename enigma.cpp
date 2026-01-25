#include <iostream>
#include "enigma.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "config.hpp"
//enigma constructor with logging
Enigma::Enigma(char pw[], RotorConfig rlc, RotorConfig rcc, RotorConfig rrc, char rc[])
: board(pw), rotorLeft(rlc), rotorCentre(rcc), rotorRight(rrc), reflex(rc)
{
    std::cout << "Enigma machine activated.\n";
}
//enigma constructor with logging
Enigma::~Enigma() {
    std::cout << "Enigma machine deactivated.\n";
}
//function to encrypt 
void Enigma::Encrypt(char &key) {
    int index = key - 'A'; //set to be the array position of variable 'k' to handle the mapping
    int &i = index;
    StepRotors(); //first steps the rotors
    board.Swap(key, i);
    std::cout << i << "plug\n";
    rotorRight.ShiftForward(i);
    std::cout << i << "rotr\n";
    rotorCentre.ShiftForward(i);
    std::cout << i << "rotc\n";
    rotorLeft.ShiftForward(i);
    std::cout << i << "rotl\n";
    reflex.Reflect(i);
    std::cout << i << "refl\n";
    rotorLeft.ShiftBackward(i);
    std::cout << i << "rotl\n";
    rotorCentre.ShiftBackward(i);
    std::cout << i << "rotc\n";
    rotorRight.ShiftBackward(i);
    std::cout << i << "rotr\n";
    board.Swap(key, i);
    std::cout << i << "plug\n";
}
//function to orchestrate rotors rotation
void Enigma::StepRotors() {
    std::cout << "Rotating right rotor...\n";
    rotorRight.Rotate();
    if(rotorRight.IsOnNotch()) {
        std::cout << "Rotating centre rotor...\n";
        rotorCentre.Rotate();
        if(rotorCentre.IsOnNotch())
        {
            std::cout << "Rotating left rotor...\n";
            rotorLeft.Rotate();
        }
    }
    else if(rotorCentre.IsOnNotch()) {
        std::cout << "Rotating centre and left rotor...\n";
        rotorCentre.Rotate(); //this simulates the 'double step' anomaly
        rotorLeft.Rotate();
    }
}