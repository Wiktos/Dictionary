template <typename K, typename V>
struct Dictionary<K, V>::Node
{
    K key;
    V info;

    int bf;
    int height;
    Node *left;
    Node *right;
};

template <typename K, typename V>
class Dictionary<K, V>::DictionaryException final : std::invalid_argument
{
    public :
        using std::invalid_argument::invalid_argument;
};

template <typename K, typename V>
void Dictionary<K, V>::insert(const key_type& new_key, const value_type& new_value){
    if(!contain(new_key, root))
        root = insert(new_key, new_value, root);
}

//***************** auxiliary functions *************************************

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::insert(const key_type& key, const value_type& val, Node *start){
    if(!start)
        return new Node{key, val, 0, 0, nullptr, nullptr};

    if(key > start->key)
        start->right = insert(key, val, start->right);
    else if(key < start->key)
        start->left = insert(key, val, start->left);

    update(start);
    return balance(start);
}

template <typename K, typename V>
void Dictionary<K, V>::update(Node *node) noexcept{
    int left_height = node->left ? node->left->height : -1;
    int right_height = node->right ? node->right->height : -1;

    node->height = left_height > right_height ? 1 + left_height : 1 + right_height;
    node->bf = right_height - left_height;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::balance(Node *node) noexcept{
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

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::llrotation(Node *node) noexcept{
    return rrotation(node);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::lrrotation(Node *node) noexcept{
    node->left = lrotation(node->left);
    return rrotation(node);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rrrotation(Node *node) noexcept{
    return lrotation(node);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rlrotation(Node *node) noexcept{
    node->right = rrotation(node->right);
    return lrotation(node);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::lrotation(Node *node) noexcept{
    Node *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rrotation(Node *node) noexcept{
    Node *new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename K, typename V>
void Dictionary<K, V>::graph(std::ostream& os, int width, Node *start) const{
    if(start) {
        if(start->right)
            graph(os, width + 8, start->right);
        if(width > 0)
            os << std::setw(width) << ' ';
        if(start->right)
            os << '\n' << std::setw(width) << ' ';

        os << '[' << start->key << ',' << start->info << "]\n";
        if(start->left) {
            os << std::setw(width) << ' ' << "\n";
            graph(os, width + 8, start->left);
        }
    }
}

template <typename K, typename V>
void Dictionary<K, V>::inorder(std::ostream& os, Node *start) const{
    if(start){
        inorder(os, start->left);
        os << start->info << ' ';
        inorder(os, start->right);
    }
}

template <typename K, typename V>
void Dictionary<K, V>::preorder(std::ostream& os, Node *start) const{
    if(start){
        os << start->info << ' ';
        preorder(os, start->left);
        preorder(os, start->right);
    }
}

template <typename K, typename V>
void Dictionary<K, V>::postorder(std::ostream& os, Node *start) const{
    if(start){
        postorder(os, start->left);
        postorder(os, start->right);
        os << start->info << ' ';
    }
}

template <typename K, typename V>
bool Dictionary<K, V>::contain(const key_type& key, Node *start) const noexcept{
    if(!start)
        return false;

    if(key > start->key)
        return contain(key, start->right);
    else if(key < start->key)
        return contain(key, start->left);
    else
        return true;
}
