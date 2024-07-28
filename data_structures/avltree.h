#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>

class Node{
    public:
    int num;
    int height;
    Node *L;
    Node *R;
};

class Avltree {
        
    int count=0;
    Node * root;
    public:
    Avltree(const std::string& filename);
    ~Avltree();
    void destruct(Node* n);
    Node * insert(Node* n,int number);
    Node * insert(int number);
    int getSize();
    Node * findMin(Node * n);
    int findMin();
    bool Search(int number);
    Node * Delete(Node* root,int number);
    Node * Delete(int number);
    Node * newNode(int number);
    int getheight(Node *n);
    int getbalance(Node *n);
    Node * rightR(Node *n);
    Node * leftR(Node *n);

};

#endif