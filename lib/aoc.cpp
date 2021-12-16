#include "aoc.hpp"

std::string trim(std::string& s) {
    size_t i = 0, j = s.size()-1;
    while (i < s.size() && isspace(s[i])) ++i;
    while (j >= 0 && isspace(s[j])) --j;
    return s.substr(i, j-i+1);
}

void split(std::string& s, std::vector<int>& res, char c) {
    res.clear();
    std::istringstream iss(s);
    std::string cur;
    while (std::getline(iss, cur, c))
        res.push_back(std::stoi(cur));
}

void split(std::string& s, std::vector<std::string>& res, char c) {
    res.clear();
    std::istringstream iss(s);
    std::string cur;
    while (std::getline(iss, cur, c))
        res.push_back(cur);
}

void split(std::string& s, std::vector<int>& res, std::string delim) {
    res.clear();
    size_t pos = 0;
    std::string cur;
    while ((pos = s.find(delim)) != std::string::npos) {
        cur = s.substr(0, pos);
        res.push_back(stoi(cur));
        s.erase(0, pos + delim.size());
    }
}

void split(std::string& s, std::vector<std::string>& res, std::string delim) {
    res.clear();
    size_t pos = 0;
    std::string cur;
    while ((pos = s.find(delim, pos)) != std::string::npos) {
        cur = s.substr(0, pos);
        res.push_back(trim(cur));
        s.erase(0, pos + delim.size());
    }
    if (s.size()) res.push_back(trim(s));
}
