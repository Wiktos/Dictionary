template <typename K, typename I>
struct Dictionary<K, I>::Node
{
    K key;
    I info;

    int bf;
    int height;
    Node *left;
    Node *right;
};

template <typename K, typename I>
class Dictionary<K, I>::DictionaryException final : std::invalid_argument
{
    public :
        using std::invalid_argument::invalid_argument;
};

template <typename K, typename I>
void Dictionary<K, I>::insert(const key_type& new_key, const value_type& new_value){
    if(is_empty()){
        root = new Node{new_key, new_value, 0, 1, nullptr, nullptr};
        return;
    }

    if(!contain(new_key, root))
        root = insert(new_key, new_value, root);
}

//***************** auxiliary functions *************************************

template <typename K, typename I>
typename Dictionary<K, I>::Node* Dictionary<K, I>::insert(const key_type& key, const value_type& val, Node *start){
    if(!start)
        return new Node{key, val, 0, 1, nullptr, nullptr};

    if(key > start->key)
        start->right = insert(key, val, start->right);
    else if(key < start->key)
        start->left = insert(key, val, start->left);

    update(start);
    return balance(start);
}

template <typename K, typename I>
void Dictionary<K, I>::update(Node *node) noexcept{
    int left_height = node->left ? node->height : 0;
    int right_height = node->right ? node->height : 0;

    node->height = left_height > right_height ? left_height : right_height;
    node->bf = right_height - left_height;
}

template <typename K, typename I>
void Dictionary<K, I>::inorder(std::ostream& os, Node *start) const{
    if(start){
        inorder(os, start->left);
        os << start->info << ' ';
        inorder(os, start->right);
    }
}

template <typename K, typename I>
bool Dictionary<K, I>::contain(const key_type& key, Node *start) const noexcept{
    if(!start)
        return false;

    if(key > start->key)
        return contain(key, start->right);
    else if(key < start->key)
        return contain(key, start->left);
    else
        return true;
}
