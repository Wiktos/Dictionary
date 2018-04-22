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
        rhs.root = nullptr;
        return *this;
    }

    //capacity
    bool is_empty() const noexcept{
        return root == nullptr;
    }
    int height() const noexcept{
        return root ? root->height : 0;
    }

    //element access
    key_type& get_max(){
        return get_max(root);
    }
    const key_type& get_max() const{
        return get_max(root);
    }
    key_type& get_min(){
        return get_min(root);
    }
    const key_type& get_min() const{
        return get_min(root);
    }
    value_type& get_value(const key_type& key){
        return get_node(key, root)->info;
    }
    const value_type& get_value(const key_type& key) const{
        return get_node(key, root)->info;
    }

    //modifiers
    void insert(const key_type& new_key, const value_type& new_value);
    void clear();
    void remove(const key_type& key);

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

    ~Dictionary() noexcept{
        clear(root);
    }

private:
    //element access
    key_type& get_max(Node *start) const;
    key_type& get_min(Node *start) const;
    Node* get_node(const key_type& key, Node *start) const;

    //modifiers
    Node* insert(const key_type& key, const value_type& val, Node *start);
    void clear(Node *start);
    Node* remove(const key_type& key, Node* start);

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
    Node* copy(Node *start);
};

#include "dictionary.tpp"
