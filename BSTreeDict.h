#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }
        
        ~BSTreeDict(){
            delete tree;
        }

        int entries() override {
            return tree->size();
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            //out << "BSTreeDict (entries: " << bs.tree->size() << " )" << std::endl;
            //bs.tree->print_inorder(out, bs.tree->root);
            return out << *(bs.tree);
        }

        void insert(std::string key, V value) override {
            TableEntry<V> entry(key, value);
            tree->insert(entry); 
        }
    
        V search(std::string key) override {
            TableEntry<V> tempEntry(key);
            TableEntry<V> found = tree->search(tempEntry);
            return found.value;
        }
    
        V remove(std::string key) override {
            TableEntry<V> tempEntry(key);
            TableEntry<V> toRemove = tree->search(tempEntry);
            V value = toRemove.value;
            tree->remove(tempEntry);
            return value;
        }

        V operator [](std::string key){
            return search(key);
        }

};

#endif
