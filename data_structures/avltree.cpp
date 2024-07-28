#include "avltree.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

Avltree::Avltree(const std::string& filename){
    std::ifstream file(filename);
    int number;
    while (file >> number) {
        this->insert(number); // insert is a class function to insert to the tree
    }
}

Avltree::~Avltree(){
    destruct(root);
}

void Avltree::destruct(Node* n) {
    if (n != nullptr) {
        destruct(n->L);
        destruct(n->R);
        delete n;
    }
}

//from build
Node* Avltree::insert(Node *n , int number) {
    if (n == nullptr) {
        count++;
        return newNode(number);
    }
    
    if (number < n->num) {
        n->L = insert(n->L, number);
    } else if (number > n->num) {
        n->R = insert(n->R, number);
    }
    
    int leftHeight = getheight(n->L);
    int rightHeight = getheight(n->R);
    
    if (leftHeight > rightHeight) {
        n->height = 1 + leftHeight;
    } else {
        n->height = 1 + rightHeight;
    }
    
    int balance = getbalance(n);
    if (balance > 1) {
        if (number < n->L->num) {
            return rightR(n);
        } else if (number > n->L->num) {
            n->L = leftR(n->L);
            return rightR(n);
        }
    }
    
    if (balance < -1) {
        if (number > n->R->num) {
            return leftR(n);
        } else if (number < n->R->num) {
            n->R = rightR(n->R);
            return leftR(n);
        }
    }
    return n;
}

//from insert
Node* Avltree::insert(int number) {
    root = insert(root, number);
    return 0;
}


int Avltree::getSize(){
    return count;
    //every time a number is added by the insert method count raises by one 
    //so count is equal to the number of times a number has been inserted to the avl tree
}

//finds the minimum value starting from the root
int Avltree::findMin(){
    Node *n = findMin(root);
        return n->num;
}

//finds the minimum value starting from the given node.
Node* Avltree::findMin(Node* n) {
    Node* current = n;
    while (current->L != nullptr) {
        current = current->L;
    }
    return current;
}

//starting from the root we search on the avl tree
//if the current node isn't the number we are looking for 
//we check if it's bigger or smaller and depending on that we move to the right or left node 
bool Avltree::Search(int number) {
    Node* comp = root;
    while (comp != nullptr) { //check if comp is not null
        if (number == comp->num) {
            return 1; //found case
        } else if (number > comp->num) {
            comp = comp->R;
        } else {
            comp = comp->L;
        }
    }
    return 0; //not found case
}


Node* Avltree::Delete(Node* root, int number) {
    if (root == nullptr){
        return root;
    }
    
    // Check if the number to delete is in the left or right subtree
    if (number < root->num) {
        root->L = Delete(root->L, number);
    } else if (number > root->num) {
        root->R = Delete(root->R, number);
    } else {
        // Node with only one child or no child
        if ((root->L == nullptr) || (root->R == nullptr)) {
            Node* temp = root->L ? root->L : root->R;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
                count--;
            } else {
                // One child case
                *root = *temp;
                count--;
            }
            delete temp; //free the memory of the temp node
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(root->R);
            root->num = temp->num;
            root->R = Delete(root->R, temp->num);
        }
    }

    if (root == nullptr) return root;

    // Update the height of the current node
    root->height = 1 + std::max(getheight(root->L), getheight(root->R));

    // Get the balance factor of this node to check whether this node became unbalanced
    int balance = getbalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getbalance(root->L) >= 0) {
        return rightR(root);
    }

    // Left Right Case
    if (balance > 1 && getbalance(root->L) < 0) {
        root->L = leftR(root->L);
        return rightR(root);
    }

    // Right Right Case
    if (balance < -1 && getbalance(root->R) <= 0) {
        return leftR(root);
    }

    // Right Left Case
    if (balance < -1 && getbalance(root->R) > 0) {
        root->R = rightR(root->R);
        return leftR(root);
    }

    return root;
}

Node* Avltree::Delete(int num) {
    root = Delete(root, num);
    return root;
}

    
Node* Avltree::newNode(int number){  
      Node* n = new Node();
      n->num = number; 
      n->height = 0;
      n->L = nullptr;  
      n->R = nullptr;   
      return(n);
}  
    
int Avltree::getheight(Node* n) {
    if (n == nullptr)
        return 0;
    return n->height;
}
 
    
int Avltree::getbalance(Node* n) {
    if (n == nullptr) {
        return 0;
    }
    return getheight(n->L) - getheight(n->R);
}

    
Node* Avltree::rightR(Node* n) {
    Node* x = n->L;
    Node* save = x->R;

    x->R = n;
    n->L = save;

    // Update heights
    int leftHeight = getheight(n->L);
    int rightHeight = getheight(n->R);
    
    if (leftHeight > rightHeight) {
        n->height = 1 + leftHeight;
    } else {
        n->height = 1 + rightHeight;
    }    
    
    leftHeight = getheight(x->L);
    rightHeight = getheight(x->R);
    
    if (leftHeight > rightHeight) {
        x->height = 1 + leftHeight;
    } else {
        x->height = 1 + rightHeight;
    }

    // Rotate and return new root
    return x;
}

      
Node* Avltree::leftR(Node* n) {
      Node* x = n->R;
      Node* save = x->L;
      
      x->L = n;
      n->R = save;
      
      // Update heights
      n->height = 1 + (getheight(n->L) > getheight(n->R) ? getheight(n->L) : getheight(n->R));
      x->height = 1 + (getheight(x->L) > getheight(x->R) ? getheight(x->L) : getheight(x->R));
      // Rotate and return new root
      return x;
}
