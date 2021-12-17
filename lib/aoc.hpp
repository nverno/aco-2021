#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

extern std::string trim(std::string&);
extern void split(std::string&, std::vector<std::string>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, std::string);
extern void split(std::string&, std::vector<std::string>&, std::string);
extern std::string hex2bin(std::string&);
