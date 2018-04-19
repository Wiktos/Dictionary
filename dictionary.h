#pragma once

#include <stdexcept>
#include <iomanip>
#include <initializer_list>

template <typename K, typename V>
class Dictionary
{
    //private member types
    struct Node;

    Node *root;

public:
    using key_type = K;
    using value_type = V;

    class DictionaryException;

    //constructors
    Dictionary() noexcept : root(nullptr)
    {}
    Dictionary(const Dictionary& source){
        root = copy(source.root);
    }
    Dictionary(Dictionary&& source) noexcept : root(std::move(root)){
        source.root = nullptr;
    }
    Dictionary(std::initializer_list<std::pair<key_type, value_type>> ls) noexcept : root(nullptr){
        for(auto curr_pair : ls)
            insert(curr_pair.first, curr_pair.second);
    }


    //operator
    Dictionary& operator=(const Dictionary& rhs){
        clear();
        root = copy(rhs.root);
        return *this;
    }
    Dictionary& operator=(Dictionary&& rhs){
        clear();
        root = std::move(rhs.root);
        return *this;
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
    void clear() noexcept{
        clear(root);
        root = nullptr;
    }

    //operations
    void graph(std::ostream& os) const{
        graph(os, 0, root);
    }
    void print_inorder(std::ostream& os) const{
        inorder(os, root);
    }
    void print_preorder(std::ostream& os) const{
        preorder(os, root);
    }
    void print_postorder(std::ostream& os) const{
        postorder(os, root);
    }
    bool contain(const key_type& key) const{
        return contain(key, root);
    }

    ~Dictionary(){
        clear(root);
    }

private:
    //modifiers
    Node* insert(const key_type& key, const value_type& val, Node *start);
    void clear(Node *start){
        if(!start)
            return;
        clear(start->left);
        clear(start->right);
        delete start;
    }

    //updating nodes and tree functions
    void update(Node *node) noexcept;
    Node* balance(Node *node) noexcept;

    //rotations performed on tree
    Node* llrotation(Node *node) noexcept;
    Node* lrrotation(Node *node) noexcept;
    Node* rrrotation(Node *node) noexcept;
    Node* rlrotation(Node *node) noexcept;

    //single rotations
    Node* lrotation(Node *node) noexcept;
    Node* rrotation(Node *node) noexcept;

    //printers
    void graph(std::ostream& os, int width, Node *start) const;
    void inorder(std::ostream& os, Node *start) const;
    void preorder(std::ostream& os, Node *start) const;
    void postorder(std::ostream& os, Node *start) const;

    //operations
    bool contain(const key_type& key, Node *start) const noexcept;
    Node* copy(Node *start){
        Node *retv = nullptr;
        if(start){
            retv = new Node{start->key, start->info, start->bf, start->height, nullptr, nullptr};
            retv->left = copy(start->left);
            retv->right = copy(start->right);
        }
        return retv;
    }
};

#include "dictionary.tpp"
