#include <algorithm>
#include "rotor.hpp"
#include "tools.hpp"
#include <iostream>
//rotor constructor, will receive the config struct as parameter
Rotor::Rotor(RotorConfig rcfg) {
    std::copy(std::begin(rcfg.ring), std::end(rcfg.ring), std::begin(Rotor::ring));
    std::copy(std::begin(rcfg.root), std::end(rcfg.root), std::begin(Rotor::root));
    notchA = rcfg.notchA;
    notchB = rcfg.notchB;
    offset = rcfg.offset;
    ringSetting = rcfg.ringSetting;

    SetRing(ringSetting); //will set rotor to specified ring setting
    Rotate(offset); //will position the rotor to specified starting positiong
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
void Rotor::Rotate(){
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
void Rotor::Rotate(int offset) {
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
void Rotor::SetRing(int ringSetting){
    for(int j = 0; j < ringSetting; j++) { //will repeat n time depending of ring setting value
        int buffer = Ctoi(root[25] + 1) % 26; //this prevents issues when the character is z
        for(int i = 25; i > 0; i--) {
            int buffer = (Ctoi(root[i - 1]) + 1) % 26;
            root[i] = Itoc(buffer);
        }
        root[0] = Itoc(buffer);
    }
    for(int i = 0; i < 26; i++) {
        std::cout << root[i];
    }
}
//function to check the notch
bool Rotor::IsOnNotch(){
    if(ring[0] == notchA || ring[0] == notchB) { //check for either possible notches
        return true;
    }
    else {
        return false;
    } 
}