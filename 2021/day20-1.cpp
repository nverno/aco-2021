// -*- compile-command: "make d20" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

vector<string> enhance(int beg, string& algo, vector<string>& img) {
    const size_t m = img.size(), n = img[0].size();
    vector<string> res(m, string(n, '.'));
    for (size_t i = beg; i+beg < m; ++i) {
        for (size_t j = beg; j+beg < n; ++j) {
            string key = img[i-1].substr(j-1,3) + img[i].substr(j-1, 3) +
                         img[i+1].substr(j-1,3);
            for (auto& c : key) c = c == '.' ? '0' : '1';
            int idx = bitset<9>(key).to_ulong();
            res[i][j] = algo[idx];
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    string algo;
    getline(cin, algo);
    assert(algo.size() == 512);
    
    vector<string> img;
    int rounds = 2, npad = rounds+1;
    string line, blank, pad = string(npad, '.');
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (img.empty()) {
            blank = string(line.size() + 2*npad, '.');
            for (int i = 0; i < npad; ++i) img.push_back(blank);
        }
        img.push_back(pad + line + pad);
    }
    for (int i = 0; i < npad; ++i)
        img.push_back(blank);

    while (rounds) {
        img = enhance(1, algo, img);
        rounds--;
    }

    std::cout << std::endl;
    for (auto& r : img) {
        cout << r << endl;
    }

    int res = 0;
    for (auto& r : img)
        for (auto& c : r)
            res += c == '#';
    cout << res << endl;
    return 0;
}
