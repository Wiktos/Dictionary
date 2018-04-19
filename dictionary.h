#pragma once

#include <stdexcept>

template <typename K, typename I>
class Dictionary
{
    //private member types
    struct Node;

    Node *root;

public:
    using key_type = int;
    using value_type = int;

    class DictionaryException;

    //constructors
    Dictionary() : root(nullptr)
    {}
    Dictionary(const Dictionary& source){
        //perform coping *this = source
    }
    Dictionary(Dictionary&& source) : root(std::move(root)){
        source.root = nullptr;
    }

    //capacity
    bool is_empty() const noexcept{
        return root == nullptr;
    }
    int height() const noexcept{
        return root ? root->height : 0;
    }

    //modifiers
    void insert(const key_type& new_key, const value_type& new_value);

    //operations
    void graph() const noexcept{
    }
    void print_inorder(std::ostream& os) const{
        inorder(os, root);
    }
    bool contain(const key_type& key) const noexcept{
        return contain(key, root);
    }

private:
    Node* insert(const key_type& key, const value_type& val, Node *start);
    void update(Node *node) noexcept;
    Node* balance(Node *node){
        if(node->bf == -2){
            //left left
            if(node->left->bf <= 0)
                return llrotation(node);
            else    //left right
                return lrrotation(node);
        }
        else if(node->bf == 2){
            //right right
            if(node->right->bf >= 0)
                return rrrotation(node);
            else    //right left
                return rlrotation(node);
        }

        //balanced
        return node;
    }
    Node* llrotation(Node *node){
        return rrotation(node);
    }
    Node* lrrotation(Node *node){
        node->left = lrotation(node->left);
        return rrotation(node);
    }
    Node* rrrotation(Node *node){
        return lrotation(node);
    }
    Node* rlrotation(Node *node){
        node->right = rrotation(node->right);
        return lrotation(node);
    }
    Node* lrotation(Node *node){
        Node *new_parent = node->right;
        node->right = new_parent->left;
        new_parent->left = node;
        update(node);
        update(new_parent);
        return new_parent;
    }
    Node* rrotation(Node *node){
        Node *new_parent = node->left;
        node->left = new_parent->right;
        new_parent->right = node;
        update(node);
        update(new_parent);
        return new_parent;
    }

    void inorder(std::ostream& os, Node *start) const;
    bool contain(const key_type& key, Node *start) const noexcept;
};

#include "dictionary.tpp"
