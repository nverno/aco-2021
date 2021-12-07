#include <bits/stdc++.h>
using namespace std;

int filter(char bit, bool ogr, vector<string>& arr) {
    const int n = arr[0].size();
    vector<string> res(arr), tmp;
    size_t cnt = 0;
    for (int i = 0; res.size() > 1 && i < n; ++i) {
        cnt = 0;
        tmp.clear();
        for (auto& x : res) {
            if (x[i] == bit) {
                tmp.push_back(x);
                if (i < n-1)
                    cnt += x[i+1] - '0';
            }
        }
        swap(tmp, res);
        if (ogr) bit = 2*cnt < res.size() ? '0' : '1';
        else bit = 2*cnt >= res.size() ? '0' : '1';
    }
    return bitset<16>(res.back()).to_ulong();
}

int main(int argc, char *argv[]) {
    vector<string> arr;
    string cur;

    int cnt = 0;
    while (cin >> cur) {
        cnt += cur[0]-'0';
        arr.push_back(cur);
    }

    int mid = arr.size()/2;
    char obit = cnt < mid ? '0' : '1',
         cbit = cnt >= mid ? '0' : '1';
    int ogr = filter(obit, true, arr),
        csr = filter(cbit, false, arr);

    cout << "ogr=" << ogr << ", csr=" << csr << endl;
    cout << ogr * csr << endl;
    return 0;
}
