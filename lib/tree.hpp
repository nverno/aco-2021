#pragma once
#include <cassert>
#include <string>
#include <stack>
#include <ostream>
#include <utility>
using std::string;
using std::stack;
using std::pair;

template<typename T>
struct Node {
    T val;
    bool leaf;
    Node *parent, *left, *right;
    int depth;
    Node(T v, Node *p=nullptr, Node *l=nullptr, Node *r=nullptr)
            : val(v), leaf(true), parent(p), left(l), right(r) {
        depth = p ? p->depth+1 : 0;
    }
    Node(Node *p=nullptr, Node *l=nullptr, Node *r=nullptr): Node(0, p, l, r) {
        leaf = false;
    }
    pair<Node*,Node*> getPair() {
        if (!(leaf && parent)) return {};
        if (parent->left == this) return {this, parent->right};
        return {parent->left, this};
    }
    Node *append(Node *nxt) {
        assert(!(left && right));
        leaf = false;
        if (!left) left = nxt;
        else right = nxt;
        return nxt;
    }
    Node *append(T v) { return append(new Node(v, this)); }
    Node *append() { return append(new Node(this)); }
    string toString() {
        if (leaf) return std::to_string(val);
        return "[" + (left ? left->toString() : "") + "," +
                (right ? right->toString() : "") + "]";
    }
    void updateDepth(int d = 0) {
        depth = d;
        if (leaf) return;
        if (left) left->updateDepth(d+1);
        if (right) right->updateDepth(d+1);
    }
    Node *clone() {
        if (leaf) return new Node(val);
        Node *res = new Node();
        if (left) {
            res->left = left->clone();
            res->left->parent = res;
            res->left->depth = depth+1;
        }
        if (right) {
            res->right = right->clone();
            res->right->parent = res;
            res->right->depth = depth+1;
        }
        res->depth = depth;
        return res;
    }
    ~Node() {
        if (parent->left == this) parent->left = nullptr;
        else parent->right = nullptr;
        if (leaf) free(this);
        else {
            if (left) left->~Node<T>();
            if (right) right->~Node<T>();
            free(this);
        }
    }
};
template<typename T>
std::ostream& operator<<(std::ostream& os, Node<T> *node) {
    os << node->toString();
    return os;
}
