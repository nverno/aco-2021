// -*- compile-command: "make d18" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

struct Node {
    int d, v;
    Node *left, *right;
    Node(int depth, int val, Node *lp=nullptr, Node* rp=nullptr)
            : d(depth), v(val), left(lp), right(rp) {
        if (left) left->right = this;
        if (right) right->left = this;
    }
    pair<Node*,Node*> getPair() {
        Node *l = left && left->d == d ? left : this,
             *r = right && right->d == d ? right : this;
        assert(l && r);
        return {l, r};
    }
    Node *explode() {
        auto [l, r] = getPair();
        if (r->right) {
            r->right->v += r->v;
            r->right->left = l;
        }
        if (l->left)
            l->left->v += l->v;
        l->v = 0;
        l->d--;
        l->right = r->right;
        return l->left && l->left->v >= 10 ? l->left : l;
    }
    Node *split() {
        if (v < 10) return this;
        d++;
        Node *nr = new Node(d, (v+1)/2, this, right);
        v /= 2;
        return nr;
    }
    Node *append(int dep, int val) {
        Node *res = new Node(dep, val, this);
        this->right = res;
        return res;
    }
};
ostream& operator<<(ostream& os, const Node *n) {
    os << n->v << "(" << n->d << ")";
    return os;
}

Node *parseLine(string& line) {
    Node *res = nullptr, *ptr = nullptr;
    int d = 0;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') continue;
        if (line[i] == '[') ++d;
        else if (line[i] == ']') --d;
        else {
            assert(isdigit(line[i]));
            if (!res) {
                res = new Node(d, line[i]-'0');
                ptr = res;
            }
            else ptr = ptr->append(d, line[i]-'0');
        }
    }
    assert(d == 0);
    return res;
}

void print(Node *n) {
    while (n) {
        cout << n << " ";
        n = n->right;
    }
    cout << "\n";
}

void add(Node *hd, Node *nxt) {
    Node *ptr = hd;
    while (ptr && ptr->right) {
        ptr->d++;
        ptr = ptr->right;
    }
    nxt->left = ptr;
    ptr->right = nxt;
    while (ptr) {
        ptr->d++;
        ptr = ptr->right;
    }
}

Node *reduce(Node *hd) {
    if (!hd) return nullptr;
    if (hd->d > 4) {
        cout << "explode: " << hd << endl;
        hd = hd->explode();
        return reduce(hd);
    }
    if (hd->v >= 10) {
        cout << "split: " << hd << endl;
        hd = hd->split();
        return reduce(hd);
    }
    hd->right = reduce(hd->right);
    return hd;
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    Node *hd = parseLine(line);

    while (getline(cin, line)) {
        Node *nxt = parseLine(line);
        add(hd, nxt);
        cout << "add: "; print(hd);
        hd = reduce(hd);
        break;
    }
    cout << endl;
    cout << "one reduction: ";
    print(hd);
    return 0;
}
