#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <vector>
#include <string>
#include "config.hpp"

MachineConfig LoadDefaultSettings(std::string model);
MachineConfig LoadCustomSettings();
MachineConfig LoadCustomSettings(std::string model);
std::string GetDateAndTime();
void SaveFile(std::vector<char> text);

#endif