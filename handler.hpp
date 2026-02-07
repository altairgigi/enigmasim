#ifndef HANDLER_HPP
#define HANDLER_HPP

//needed libraries for return types
#include <vector>
#include <string>
#include "config.hpp"

MachineConfig LoadDefaultSettings(std::string model);
MachineConfig LoadCustomSettings();
MachineConfig LoadCustomSettings(std::string model);
void SaveFile(std::vector<char> text);

#endif