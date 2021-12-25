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

void fillRing(size_t b, size_t e, char c, vector<string>& img) {
    const size_t m = img.size(), n = img[0].size();
    for (size_t i = b; i <= e; ++i) {
        fill(img[i].begin()+b, img[i].end()-b-1, c);
        fill(img[m-i-1].begin()+b, img[m-i-1].end()-b-1, c);
    }
    for (size_t i = b; i+b < m; ++i)
        for (size_t j = b; j <= e; ++j)
            img[i][j] = img[i][n-j-1] = c;
}

int main(int argc, char *argv[]) {
    string algo;
    getline(cin, algo);
    assert(algo.size() == 512);
    
    vector<string> img;
    int rounds = 50, npad = rounds+1;
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

    for (int i = rounds, cnt = 0; i > 0; --i, ++cnt) {
        fillRing(i-1, i, (cnt&1) ? '#' : '.', img);
        img = enhance(i, algo, img);
        // std::cout << std::endl;
        // for (auto& r : img) {
        //     cout << r << endl;
        // }
    }

    int res = 0;
    for (size_t i = 1; i+1 < img.size(); ++i) {
        for (size_t j = 1; j+1 < img[0].size(); ++j) {
            res += img[i][j] == '#';
        }
    }
    cout << res << endl;
    return 0;
}
