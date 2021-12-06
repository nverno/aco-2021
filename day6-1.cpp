#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    string num;

    std::priority_queue<int, vector<int>, std::greater<>> pq;
    int cnt = 0;
    while (getline(iss, num, ',')) {
        pq.push(stoi(num));
        cnt++;
    }

    int days = 80;
    while (!pq.empty()) {
        int f = pq.top(); pq.pop();
        if (f >= days) break;
        pq.push(f + 7);
        pq.push(f + 9);
        ++cnt;
    }
    cout << cnt << endl;    
    return 0;
}
