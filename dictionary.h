#pragma once

#include <stdexcept>
#include <iomanip>

template <typename K, typename I>
class Dictionary
{
    //private member types
    struct Node;

    Node *root;

public:
    using key_type = K;
    using value_type = I;

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
    void graph() const{
        graph(0, root);
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

private:
    //modifiers
    Node* insert(const key_type& key, const value_type& val, Node *start);

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
    void graph(int width, Node *start) const{
        if(start) {
            if(start->right)
                graph(width + 8, start->right);
            if(width)
                std::cout << std::setw(width) << ' ';
            if(start->right)
                std::cout << '\n' << std::setw(width) << ' ';
            std::cout<< start->key << "\n";
            if(start->left) {
                std::cout << std::setw(width) << ' ' << "\n";
                graph(width + 8, start->left);
            }
        }
    }
    void inorder(std::ostream& os, Node *start) const;
    void preorder(std::ostream& os, Node *start) const;
    void postorder(std::ostream& os, Node *start) const;

    //operations
    bool contain(const key_type& key, Node *start) const noexcept;
};

#include "dictionary.tpp"
