#include <algorithm>
#include "plugboard.hpp"
#include "config.hpp"
//plugboard constructor
Plugboard::Plugboard(char pw[]) {
    std::copy(pw, pw + 26, plugs);
}
//function to swap the key
void Plugboard::Swap(char &key, int &index) {
    key = plugs[index];
    index = plugs[index] - 'A';
}