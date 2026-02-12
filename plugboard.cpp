#include <algorithm>
#include "plugboard.hpp"
#include "tools.hpp"

//plugboard constructor
Plugboard::Plugboard(PlugboardConfig pcfg) {
    std::copy(std::begin(pcfg.plugs), std::end(pcfg.plugs), std::begin(Plugboard::plugs));
}

//function to swap the key
void Plugboard::Swap(char &key, int &index) {
    key = plugs[index];
    index = Ctoi(plugs[index]);
}