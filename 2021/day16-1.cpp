// -*- compile-command: "make d16" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int parseLiteral(size_t& pos, string& s) {
    string lit;
    while (pos < s.size() && s[pos] == '1') {
        lit += s.substr(++pos, 4);
        pos += 4;
    }
    if (pos + 5 <= s.size()) {
        assert(s[pos] == '0');
        lit += s.substr(++pos, 4);
        pos += 4;
    }
    return bitset<64>(lit).to_ulong();
}

pair<int,int> parseHeader(size_t& pos, string& s) {
    int v = bitset<3>(s.substr(pos, 3)).to_ulong(),
        id = bitset<3>(s.substr(pos+3, 3)).to_ulong();
    pos += 6;
    return {v, id};
}

int main(int argc, char *argv[]) {
    std::unordered_map<char,string> m = {
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
    string line, bits;
    getline(cin, line);
    for (char const &c: line)
        bits += m[c];

    const size_t n = bits.size();
    int res = 0;
    size_t pos = 0;
    while (pos+6 < bits.size()) {
        auto [ver, id] = parseHeader(pos, bits);
        res += ver;
        if (id == 4) {
            int v = parseLiteral(pos, bits);
            (void)v;
        } else {
            char mode = bits[pos++];
            int sz = mode == '0' ? 15 : 11,
                len = bitset<16>(bits.substr(pos, sz)).to_ulong();
            (void)len;
            pos += sz;
        }
    }
    if (pos < n)
        cout << "skipped from pos = " << pos << ": " << bits.substr(pos) << endl;
    
    cout << res << endl;
    return 0;
}
