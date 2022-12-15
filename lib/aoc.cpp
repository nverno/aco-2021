#include "aoc.hpp"

std::vector<int> read_ints(std::string s) {
    int n = s.size();
    std::vector<int> res;
    int v = 0, sgn = 1;
    bool active = false;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '-' && i < n-1 && isdigit(s[i+1])) {
            active = true;
            sgn = -1;
        } else if (isdigit(s[i])) {
            active = true;
            v = 10*v + (s[i] - '0');
        } else {
            if (active) res.push_back(sgn * v);
            v = 0;
            sgn = 1;
            active = false;
        }
    }
    if (active) res.push_back(sgn * v);
    return res;
}

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
    if (s.size()) res.push_back(stoi(s));
}

void split(std::string& s, std::vector<std::string>& res, std::string delim) {
    res.clear();
    size_t pos = 0, n = delim.size();
    std::string cur;
    while ((pos = s.find(delim)) != std::string::npos) {
        cur = s.substr(0, pos);
        res.push_back(trim(cur));
        s.erase(0, pos + n);
    }
    if (s.size()) res.push_back(trim(s));
}

std::string hex2bin(std::string& s) {
    static std::unordered_map<char,std::string> m = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"},
    };
    std::string bits;
    for (char const &c: s) bits += m[std::toupper(c)];
    return bits;
}

#ifdef USE_RE
bool matches(std::string& line, std::vector<string>& res, std::string re) {
    res.clear();
    std::regex r(re);
    std::smatch sm;
    while (std::regex_search(line, sm, r)) {
        res.push_back(sm.str());
        line = sm.suffix();
        return true;
    }
    return false;
}
#endif
