#include <algorithm>
#include "reflector.hpp"
#include "config.hpp"
//reflector constructor, will receive as parameter the array config
Reflector::Reflector(char rc[]) {
    std::copy(rc, rc + 26, map);
}
//function to reflect the signal
void Reflector::Reflect(int &index) {
    index = map[index] - 'A';
}