#pragma once
// https://github.com/dkknk/kyopro/blob/main/lib/data-structure/splay_tree.hpp
template<typename T>
struct splay_tree{
    struct Node{
        Node *left,*right,*parent;
        T val;
        Node(T val) : left(nullptr),right(nullptr),parent(nullptr),val(val){}
    };
    Node* root = nullptr;
    splay_tree(){}
};