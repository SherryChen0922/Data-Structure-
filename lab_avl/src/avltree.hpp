/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(t == NULL) {
        return;
    }
    Node* r = t -> right;
   // Node* l = t;
    t ->right= r -> left;
    r -> left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = r;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if(t == NULL) {
        return;
    }
    Node* l = t -> left;
   // Node* r = t;
    //t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t -> left = l -> right;
    l ->right = t;
     t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = l;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL) {return;}
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balance == -2) {
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(l_balance == -1) {rotateRight(subtree);}
        else {rotateLeftRight(subtree);}
    } else if(balance == 2) {
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(r_balance == 1) {rotateLeft(subtree);}
        else {rotateRightLeft(subtree);}
    }
   subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==NULL) {subtree = new Node(key,value);} 
    else if(key < subtree->key) {insert(subtree->left, key, value);}
    else if(key > subtree->key) {insert(subtree->right,key,value); }
    else {return;}
   // subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
    rebalance(subtree);
   // subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree ->left,key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
       // Node* tmp1 = subtree;
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* tmp2 = subtree;
         tmp2 = subtree -> left;
         while(tmp2 -> right != NULL) {
            tmp2 = tmp2 -> right;
         }
        swap(subtree, tmp2);
        remove(subtree ->left, tmp2->key);
        } else {
            /* one-child remove */
            // your code here
           Node* tmp = subtree;
            if(subtree->left != NULL) {
                subtree = subtree->left;
                 delete tmp;
                tmp = NULL;
            } else if(subtree->right != NULL){
                //tmp = subtree->right;
                subtree = subtree->right;
                 delete tmp;
                tmp = NULL;
            }
        }
}
//subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
  rebalance(subtree);
  //subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
}
// Node*& tmp1 = find(subtree, key);
//     if(tmp1 == NULL) {
//         return;
//     }
//     if (tmp1 -> left == NULL && tmp1 -> right == NULL)
//     {
//         delete tmp1;
//         tmp1 = NULL;
//     } else if (tmp1 -> left == NULL) {
//          Node* tmp2 = tmp1;
//          tmp1 = tmp1 ->right;
//          delete tmp2;
//          tmp2 = NULL;
//     } else if(tmp1->right == NULL){
//         Node* tmp2 = tmp1;
//          tmp1 = tmp1 ->left;
    //      delete tmp2;
    //      tmp2 = NULL;
    // } else {
    //     Node* tmp2 = tmp1;
    //      tmp2 = tmp1 -> left;
    //      while(tmp2 -> right != NULL) {
    //         tmp2 = tmp2 -> right;
    //      }
    //     std::cout << tmp2 -> key << std::endl;
    //     swap(tmp1, tmp2);
    //     std::cout << tmp2 -> key << std::endl;
    //     remove(tmp1 ->left, tmp2 ->key);
    
    // }