// -*- compile-command: "make d13" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

struct node {
    int val;
    node* next, *sub;
    node(int v = -1): val(v), next(nullptr), sub(nullptr) {}
};

node *parse_list(int& i, string& line) {
    int n = line.size();
    if (i >= n) return nullptr;
    if (line[i] == ',' || line[i] == ' ')
        return parse_list(++i, line);
    if (line[i] == ']') {
        ++i;
        return nullptr;
    }
    node *res = new node(-1);
    if (line[i] == '[') {
        res->sub = parse_list(++i, line);
        res->next = parse_list(i, line);
        return res;
    }
    int v = 0;
    while (i < n && isdigit(line[i])) {
        v = 10*v + (line[i] - '0');
        ++i;
    }
    res->val = v;
    res->next = parse_list(i, line);
    return res;
}

ostream& operator<<(ostream& os, node *n) {
    if (!n) return os;
    if (n->sub || n->val < 0) os << '[' << n->sub << ']';
    else os << n->val;
    if (n->next) os << ',';
    return os << n->next;
}

int cmp(node *a, node *b, int d = 0) {
    // cout << string(d, ' ') << "- Compare: " << a << " vs " << b << '\n';
    if (!(a || b)) return 0;
    if (!a) return -1;
    if (!b) return 1;
    if (a->val >= 0 && b->val >= 0) {
        assert(!(a->sub || b->sub));
        int diff = a->val - b->val;
        return diff == 0 ? cmp(a->next, b->next, d+2) : diff;
    }
    if (a->sub && b->sub) {
        int res = cmp(a->sub, b->sub, d+2);
        return res == 0 ? cmp(a->next, b->next, d+2) : res;
    }
    if (!(a->sub || b->sub)) return a->val - b->val;
    if (!a->sub && a->val == -1) return -1;
    if (!b->sub && b->val == -1) return 1;
    node *as = a->sub ? a->sub : new node(a->val),
         *bs = b->sub ? b->sub : new node(b->val);
    int res = cmp(as, bs, d+2);
    return res == 0 ? cmp(a->next, b->next, d+2) : res;
}

int main(int argc, char *argv[]) {
    string sa, sb;
    int res = 0, idx = 1;
    while (getline(cin, sa)) {
        if (sa.empty()) continue;
        getline(cin, sb);
        int i = 0, j = 0;
        node *a = parse_list(i, sa),
             *b = parse_list(j, sb);
        if (cmp(a, b) <= 0) 
            res += idx;
        ++idx;
    }

    cout << res << '\n';
    return 0;
}
