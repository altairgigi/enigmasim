#include <algorithm>
#include "rotor.hpp"
#include "tools.hpp"

//rotor constructor, will receive the config struct as parameter
Rotor::Rotor(RotorConfig rcfg) {
    std::copy(std::begin(rcfg.ring), std::end(rcfg.ring), std::begin(Rotor::ring));
    std::copy(std::begin(rcfg.root), std::end(rcfg.root), std::begin(Rotor::root));
    notchA = rcfg.notchA;
    notchB = rcfg.notchB;
    offset = rcfg.offset;
    ringSetting = rcfg.ringSetting;

    SetRing(); //will set rotor to specified ring setting
    SetGround(); //will position the rotor to specified starting positiong
}

//funtion to shift the signal forward
void Rotor::ShiftForward(int &index) {
    index = ((Ctoi(root[index]) - offset) + 26) % 26; //this protection hanldes possible negative index
}

//funtion to shift the signal backward
void Rotor::ShiftBackward(int &index) {
    int i = 0;
    while(root[i] != ring[index]) {
        i++;
    }
    index = i; //no need to handle negative index because loop looks for actual index
}

//function to simulate rotation
void Rotor::Rotate() {
    char buffer1 = ring[0];
    char buffer2 = root[0];
    for(int i = 0; i < 25; i++) { //moves forward both arrays thus simulating the rotation
        ring[i] = ring[i + 1];
        root[i] = root[i + 1];
    }
    ring[25] = buffer1;
    root[25] = buffer2;
    offset++; //increase offset to take into accout the moved index
    offset = offset % 26; //if offset goes beyond the array size is then set back to 0
}

//function to simulate grundstellung
void Rotor::SetGround() {
    for(int j = 0; j < offset; j++) { //will repeat n time depending of offset value
        char buffer1 = ring[0];
        char buffer2 = root[0];
        for(int i = 0; i < 25; i++) { //moves forward both arrays thus simulating the rotation
            ring[i] = ring[i + 1];
            root[i] = root[i + 1];
        }
        ring[25] = buffer1;
        root[25] = buffer2;
    }
}

//function to simulate the ringastellung
void Rotor::SetRing() {
    for(int j = 0; j < ringSetting; j++) { //will repeat n time depending of ring setting value
        int bufferA = Ctoi(root[25] + 1) % 26; //this prevents issues when the character is z
        for(int i = 25; i > 0; i--) {
            int bufferB = (Ctoi(root[i - 1]) + 1) % 26;
            root[i] = Itoc(bufferB);
        }
        root[0] = Itoc(bufferA);
    }
}

//function to check the notch
bool Rotor::IsOnNotch() {
    if(ring[0] == notchA || ring[0] == notchB) { //check for either possible notches
        return true;
    }
    else {
        return false;
    } 
}

//function to get the rotor position (shown in the box)
char Rotor::GetPos() const {
    return ring[0];
}