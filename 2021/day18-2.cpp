// -*- compile-command: "make d18" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
#include "../lib/tree.hpp"
using namespace std;
using Tree = Node<int>;

// [[[a,b]],[d,e]...]
Tree *treeFromList(std::string& line) {
    Tree *res = nullptr;
    std::stack<Tree*> st;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') continue;
        if (line[i] == '[') {
            if (st.empty()) st.push(new Tree());
            else st.push(st.top()->append());
        }
        else if (line[i] == ']') res = st.top(), st.pop();
        else {
            assert(isdigit(line[i]));
            st.top()->append(line[i]-'0');
        }
    }
    return res;
}

Tree *link(Tree *t, Tree *prev) {
    if (t->leaf) {
        t->left = prev;
        if (prev) prev->right = t;
        return t;
    }
    Tree *l = link(t->left, prev);
    return link(t->right, l);
}

Tree *getHead(Tree *t) {
    while (t && t->left) t = t->left;
    return t;
}

Tree *join(Tree *l, Tree *r) {
    Tree *res = new Tree(nullptr, l, r);
    l->parent = r->parent = res;
    res->updateDepth();
    link(res, nullptr);
    return res;
}

Tree *explode(Tree *t) {
    assert(t && t->leaf && t->depth >= 4);
    auto [l, r] = t->getPair();
    assert(l->leaf && r->leaf);
    if (l->left) l->left->val += l->val;
    if (r->right) r->right->val += r->val;
    Tree *res = l->parent;
    res->left = l->left;
    res->right = r->right;
    res->val = 0;
    res->leaf = true;
    if (l->left) l->left->right = res;
    if (r->right) r->right->left = res;
    free(l); free(r);
    return res;
}

Tree *split(Tree *t) {
    assert(t && t->leaf && t->val >= 10);
    Tree *l = t->left, *r = t->right;
    t->left = new Tree(t->val/2, t, l);
    t->right = new Tree((1+t->val)/2, t, t->left, r);
    t->left->right = t->right;
    if (l) l->right = t->left;
    if (r) r->left = t->right;
    t->leaf = false;
    return t->left;
}

Tree *reduce(Tree *t) {
    Tree *ptr = getHead(t);
    while (ptr) {
        assert(ptr->leaf);
        if (ptr->depth > 4) ptr = explode(ptr);
        else ptr = ptr->right;
    }
    ptr = getHead(t);
    while (ptr) {
        assert(ptr->leaf);
        if (ptr->val >= 10) {
            split(ptr);
            return reduce(t);
        } else ptr = ptr->right;
    }
    return t;
}

void printList(Tree *hd) {
    cout << "list: ";
    while (hd && hd->right) {
        cout << hd->val << "(" << hd->depth << ")" << ",";
        hd = hd->right;
    }
    cout << hd->val << endl;
}

int magnitude(Tree *t) {
    if (!t) return 0;
    if (t->leaf) return t->val;
    return 3*magnitude(t->left) + 2*magnitude(t->right);
}
int add(Tree *l, Tree *r) {
    Tree *t = join(l->clone(), r->clone());
    int res = magnitude(reduce(t));
    free(t);
    return res;
}

int main(int argc, char *argv[]) {
    vector<Tree*> trees;
    string line;
    while (getline(cin, line))
        trees.push_back(treeFromList(line));
    
    int res = 0;
    for (size_t i = 0; i < trees.size(); ++i) {
        for (size_t j = i+1; j < trees.size(); ++j) {
            res = max({ res, add(trees[i], trees[j]), add(trees[j], trees[i]) });
        }
    }
    cout << res << endl;
    return 0;
}
