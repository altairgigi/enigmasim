#include <algorithm>
#include "reflector.hpp"
#include "tools.hpp"

//reflector constructor, will receive as parameter the array config
Reflector::Reflector(ReflectorConfig rcfg) {
    std::copy(std::begin(rcfg.map), std::end(rcfg.map), std::begin(Reflector::map));
}

//function to reflect the signal
void Reflector::Reflect(int &index) {
    index = Ctoi(map[index]);
}