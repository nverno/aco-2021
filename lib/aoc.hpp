#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <tuple>
#ifdef USE_RE
# include <regex>
#endif 
#include "tree.hpp"

extern std::vector<int> read_ints(std::string s);
extern std::string trim(std::string&);
extern void split(std::string&, std::vector<std::string>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, char c = ' ');
extern void split(std::string&, std::vector<int>&, std::string);
extern void split(std::string&, std::vector<std::string>&, std::string);
extern std::string hex2bin(std::string&);
#ifdef USE_RE
extern bool matches(std::string&, std::vector<string>&, std::string);
#endif 
