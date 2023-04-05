/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    if(root == NULL) {
        return V();
    }
    Node*& output = this->find(root,key);
    return output -> value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == NULL || subtree -> key == key) {
        return subtree;
    }
    if(subtree -> key < key) {
        return find(subtree -> right, key);
    } else {
        return find(subtree-> left, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
   insert(root,key, value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    Node* & e = find(root, key);
    if(e == NULL) {
        e = new Node(key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    K tmp1 = first -> key;
    V tmp2 = first -> value;
    first -> key = second -> key;
    first -> value = second -> value;
    second -> key = tmp1;
    second -> value = tmp2;

}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root,key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    Node*& tmp1 = find(subtree, key);
    if(tmp1 == NULL) {
        return;
    }
    if (tmp1 -> left == NULL && tmp1 -> right == NULL)
    {
        delete tmp1;
        tmp1 = NULL;
    } else if (tmp1 -> left == NULL) {
         Node* tmp2 = tmp1;
         tmp1 = tmp1 ->right;
         delete tmp2;
         tmp2 = NULL;
    } else if(tmp1->right == NULL){
        Node* tmp2 = tmp1;
         tmp1 = tmp1 ->left;
         delete tmp2;
         tmp2 = NULL;
    } else {
        Node* tmp2 = tmp1;
         tmp2 = tmp1 -> left;
         while(tmp2 -> right != NULL) {
            tmp2 = tmp2 -> right;
         }
        std::cout << tmp2 -> key << std::endl;
        swap(tmp1, tmp2);
        std::cout << tmp2 -> key << std::endl;
        remove(tmp1 ->left, tmp2 ->key);
    
    }
}
template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> output;
    for(unsigned i = 0; i < inList.size();i++) {
        output.insert(inList[i].first, inList[i].second);
    }
    return output;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here 
    std::vector<int> output;
    for(unsigned i = 0; i < inList.size();i++) {
        output.push_back(0);
    }
    unsigned size = inList.size();
    std::sort (inList.begin(),inList.end());
    do {
        BST<K,V> tocount = listBuild(inList);
        output[tocount.height()] = output[tocount.height()] + 1;
    } while (std::next_permutation(inList.begin(), inList.end()));
    return output;
}