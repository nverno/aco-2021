#include <bits/stdc++.h>
using namespace std;

// trie version- O(n*|nums|)
struct Node {
    int nchild, ones;
    string val;
    Node *ch[2];
    Node(): nchild(0), ones(0) {
        memset(ch, 0, 2 * sizeof(Node*));
    }
};

Node *root;
void add(string num) {
    Node *ptr = root;
    for (char const &c: num) {
        ptr->nchild++;
        ptr->ones += c-'0';
        if (!ptr->ch[c-'0'])
            ptr->ch[c-'0'] = new Node();
        ptr = ptr->ch[c-'0'];
    }
    ptr->val = num;
}

int main(int argc, char *argv[]) {
    root = new Node();
    string cur;
    while (cin >> cur) add(cur);

    Node *ptr = root;
    while (ptr && ptr->nchild > 1) {
        if (ptr->ones >= ptr->nchild - ptr->ones)
            ptr = ptr->ch[0];
        else ptr = ptr->ch[1];
    }
    while (ptr) {
        if (ptr->val.size() > 0) break;
        if (ptr->ch[0]) ptr = ptr->ch[0];
        else ptr = ptr->ch[1];
    }
    assert(ptr);
    int csr = bitset<16>(ptr->val).to_ulong();

    ptr = root;
    while (ptr && ptr->nchild > 1) {
        if (2 * ptr->ones < ptr->nchild)
            ptr = ptr->ch[0];
        else ptr = ptr->ch[1];
    }
    assert(ptr);
    int ogr = bitset<16>(ptr->val).to_ulong();
    
    cout << "ogr=" << ogr << ", csr=" << csr << endl;
    cout << ogr * csr << endl;
    return 0;
}
