#pragma once

#include <stdexcept>

//template <typename Key, typename Info>
class Dictionary
{
    //private member types
    struct Node
    {
        int key;
        int info;

        int bf;
        int height;
        Node *left;
        Node *right;

        void insert_child(Node *child) {
            if(key > child->key && !left)
                left = child;
            else if(key < child->key && !right)
                right = child;
        }
    };

    Node *root;

public:
    class DictionaryException final : std::invalid_argument
    {
        public :
            using std::invalid_argument::invalid_argument;
    };

    //constructors
    Dictionary() : root(nullptr)
    {}
    Dictionary(const Dictionary& source) {
        //perform coping *this = source
    }
    Dictionary(Dictionary&& source) : root(std::move(root))
    {
        source.root = nullptr;
    }

    //capacity
    bool is_empty() const noexcept {
        return root == nullptr;
    }
    int height() const noexcept {
        return root ? root->height : 0;
    }

    //modifiers
    void insert(int new_key, int new_info){
        if(is_empty()){
            root = new Node{new_key, new_info, 0, 1, nullptr, nullptr};
            return;
        }

        //throws DictionaryException if new_key already exist in tree
        Node* parent = find_parent(new_key, root);

        Node *new_node = new Node{new_key, new_info, 0, 1, nullptr, nullptr};
        parent->insert_child(new_node);

        //update - perform rotation where needed
    }

    //operations
    bool contain(const int key){
        return true;
    }

private:
    Node* find_parent(int key, Node *start) {
        if(start->key > key)
            return !start->left ? start : find_parent(key, start->left);
        else if(start->key < key)
            return !start->right ? start : find_parent(key, start->right);

        //key already exist in tree
        throw DictionaryException("Key already exist in the tree");
    }
};
