#include <algorithm>
#include "rotor.hpp"
//rotor constructor, will receive the config struct as parameter
Rotor::Rotor(RotorConfig rcfg) {
    std::copy(std::begin(rcfg.ring), std::end(rcfg.ring), std::begin(Rotor::ring));
    std::copy(std::begin(rcfg.root), std::end(rcfg.root), std::begin(Rotor::root));
    notchA = rcfg.notchA;
    notchB = rcfg.notchB;
    offset = rcfg.offset;
}
//funtion to shift the signal forward
void Rotor::ShiftForward(int &index) {
    index = (root[index] - 'A') - offset;
    if(index < 0){ //check to handle possible negative index due to offset
        index+=26;
    }
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
    for(int i = 0; i < 25; i++) {
        ring[i] = ring[i + 1];
        root[i] = root[i + 1];
    }
    ring[25] = buffer1;
    root[25] = buffer2;
    offset++;
    if(offset >= 26){ //if offset goes beyond the array is set back to 0
        offset-=26;
    }
}
//function to simulate the ringastellung
void Rotor::SetRing(){
    char buffer = root[25];
    for(int i = 24; i > 0; i--) {
        root[i] = root[i - 1];
    }
    root[0] = buffer;
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