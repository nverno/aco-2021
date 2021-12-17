// -*- compile-command: "make d16" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll unsigned long long
#define DEBUG 1

ll parseLiteral(size_t& pos, string& s) {
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
    ll res = bitset<64>(lit).to_ullong();
#ifdef DEBUG
    cout << "parseLiteral(" << lit << ") = " << res << endl;
#endif /* DEBUG */
    return res;
}

pair<int,int> parseHeader(size_t& pos, string& s) {
    int v = bitset<3>(s.substr(pos, 3)).to_ulong(),
        id = bitset<3>(s.substr(pos+3, 3)).to_ulong();
    pos += 6;
    return {v, id};
}

void print(int id, ll res, vector<ll>& vals) {
    char op = id == 0 ? '+'
              : id == 1 ? '*'
              : id == 2 ? 'm'
              : id == 3 ? 'M'
              : id == 5 ? '>'
              : id == 6 ? '<'
              : id == 7 ? '='
              : '?';
    cout << op << "(";
    for (size_t i = 0; i < vals.size(); ++i) {
        cout << vals[i];
        if (i < vals.size()-1) cout << ",";
    }
    cout << ") = " << res << endl;
}

ll parse(size_t& pos, string& bits) {
    assert(pos+6 <= bits.size());
    auto [_, id] = parseHeader(pos, bits);
    if (id == 4)
        return parseLiteral(pos, bits);
        
    char mode = bits[pos++];
    int sz = mode == '0' ? 15 : 11,
       len = bitset<16>(bits.substr(pos, sz)).to_ulong();
    pos += sz;

    vector<ll> vals;
    if (mode == '0') {
        string bs = bits.substr(pos, len);
        pos += len;
        size_t j = 0;
        while (j < bs.size())
            vals.push_back(parse(j, bs));
    } else {
        while (len--)
            vals.push_back(parse(pos, bits));
    }

    ll res;
    if (id == 0) res = accumulate(vals.begin(), vals.end(), 0LL);
    else if (id == 1) res = accumulate(vals.begin(), vals.end(), 1LL, multiplies<>());
    else if (id == 2) res = *min_element(vals.begin(), vals.end());
    else if (id == 3) res = *max_element(vals.begin(), vals.end());
    else if (id == 5) res = vals[0] > vals[1];
    else if (id == 6) res = vals[0] < vals[1];
    else if (id == 7) res = vals[0] == vals[1];
    else assert(false);

#ifdef DEBUG
    print(id, res, vals);
#endif /* DEBUG */
    return res;
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    string bits = hex2bin(line);

    size_t pos = 0;
    ll res = parse(pos, bits);
    if (pos < bits.size())
        cout << "skipped from pos = " << pos << ": " << bits.substr(pos) << endl;
    
    cout << res << endl;
    return 0;
}
