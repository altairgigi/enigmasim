#ifndef ROTOR_HPP
#define ROTOR_HPP
//include config.hpp for RotorConfig struct in constructor declaration
#include "config.hpp"
//declaration of the rotor class
class Rotor {
    public:
        Rotor(RotorConfig rotorCfg);
        void ShiftForward(int &index);
        void ShiftBackward(int &index);
        void Rotate(); //this will handle both rotation
        void Rotate(int offset); //this will handle grundstellung (i.e. ground setting) through offset value
        void SetRing(int ring); //this will handle ringastellung (i.e. ring setting) through ringSetting value
        bool IsOnNotch(); //this will check if the rotor is on the notch
    private:
        char ring[26]; //this represent the reifen i.e. the alphabet ring
        char root[26]; //this represent the wursel i.e. the internal setting
        int notchA;
        int notchB;
        int offset;
        int ringSetting;
};

#endif