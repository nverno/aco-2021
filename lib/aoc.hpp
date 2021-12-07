#pragma once

#include <string>
#include <sstream>
#include <vector>

extern void split(std::string&, std::vector<std::string>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, std::string);
