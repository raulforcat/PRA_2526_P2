#ifndef BSTREE_H
#define BSTREE_H

#include "BSNode.h"
#include <iostream>
#include <stdexcept>
#include <ostream>

template <typename T>
class BSTree {
private:
    int nelem;             
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Element not found in BSTree");
        }
        
        if (e == n->elem) {
            return n;
        } else if (e < n->elem) {
            return search(n->left, e);
        } else {
            return search(n->right, e);
        }
    }
    
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            return new BSNode<T>(e);
        }
        
        if (e == n->elem) {
            throw std::runtime_error("Element already exists in BSTree");
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else {
            n->right = insert(n->right, e);
        }
        
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const{
        if (n != nullptr){
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("ElementNotFoundException");
        } else if (n->right != nullptr) {
            return max(n->right);
        } else {
            return n->elem;
        }
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            return n->left;
        } else {
            n->right = remove_max(n->right);
            return n;
        }
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
      if (n == nullptr) {
            throw std::runtime_error("ElementNotFoundException");
        } else if (e > n->elem) { 
            n->right = remove(n->right, e);
        } else if (e < n->elem) { 
            n->left = remove(n->left, e);
        } else {
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
                nelem--;
            } else {
                BSNode<T>* temp = n;
                n = (n->left != nullptr) ? n->left : n->right;
                delete temp;
                nelem--;
            }
        }
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:

    BSTree() : nelem(0), root(nullptr) {}

    int size() const {
        return nelem;
    }

    T search(T e) const {
        BSNode<T>* node = search(root, e);
        return node->elem;
    }
    
    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }

    void remove(T e) {
        root = remove(root, e);  // root = remove(r, e) como en pseudocódigo
    }

    ~BSTree() {
        delete_cascade(root);
    }

};

#endif
