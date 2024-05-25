//
// Created by antilopa on 23.05.24.
//

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "LinkedList.h"

enum PATH{
    LEFT, RIGHT, PARENT
};

enum ORDER{
    PREORDER, INORDER, POSTORDER
};

template<typename T>
struct BinaryNode{
    int key;
    T value;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
    int height = 0;
    BinaryNode(int key, T value){ this->key = key; this->value = value;}
};

template <typename T>
class BinarySearchTree{
protected:
    BinaryNode<T>* top;
    static void insert(BinaryNode<T>& node, int key, T value);
    static BinaryNode<T>* search(BinaryNode<T>* node, int key);
    static BinaryNode<T>* getMin(BinaryNode<T>* node);
    static BinaryNode<T>* getMax(BinaryNode<T>* node);
    static int getHeight(BinaryNode<T>* node);
    static void updateHeight(BinaryNode<T>* node);
    static int getBalance(BinaryNode<T>* node);
    static void swap(BinaryNode<T>* a, BinaryNode<T>* b);
    static void rightRotate(BinaryNode<T>* node);
    static void leftRotate(BinaryNode<T>* node);
    static void balance(BinaryNode<T>* node);
    static BinaryNode<T>* Delete(BinaryNode<T>* node, int key);
    static void PrintTree(BinaryNode<T>* node);
    static void DeleteTree(BinaryNode<T>* node);
    static void CopyTree(BinaryNode<T>* node);
    static void EnQueueLeft(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node);
    static void EnQueueRight(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node);
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& searchTree);
    int GetHeight();
    bool Contains(T item);
    void Insert(int key, const T& item);
    void Remove(T item);
    void Remove(int key);
    int Find(T item);
    T* Find(int key);
    T* Find(const LinkedList<PATH>& list);
    void ForEach(void (*action)(T));
    void Traverse(void (*action)(T), ORDER order);
    ~BinarySearchTree();
};


//protected


template <typename T>
void BinarySearchTree<T>::insert(BinaryNode<T>& node, int key, T value){
    if(key<node.key){
        if(node.left == nullptr){
            node.left = new BinaryNode(key, value);
        }
        else insert(*node.left, key, value);
    }
    else if(key>=node.key){
        if(node.right == nullptr){
            node.right = new BinaryNode(key, value);
        }
        else insert(*node.right, key, value);
    }
};

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::search(BinaryNode<T>* node, int key){
    if(node == nullptr) return nullptr;
    if(node->key == key) return node;
    return (key<node->key)?search(node->left, key):search(node->right, key);
};

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::getMin(BinaryNode<T>* node){
    if(node == nullptr) return nullptr;
    if(node->left == nullptr) return node;
    return getMin(node->left);
};

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::getMax(BinaryNode<T>* node){
    if(node == nullptr) return nullptr;
    if(node->right == nullptr) return node;
    return getMax(node->right);
};

template <typename T>
int BinarySearchTree<T>::getHeight(BinaryNode<T>* node){
    return node== nullptr?-1:node->height;
};

template <typename T>
void BinarySearchTree<T>::updateHeight(BinaryNode<T>* node){
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    node->height = ((leftHeight>rightHeight)?leftHeight:rightHeight)+1;
};

template <typename T>
int BinarySearchTree<T>::getBalance(BinaryNode<T>* node){
    return (node == nullptr)?0: getHeight(node->right) - getHeight(node->left);
};

template <typename T>
void BinarySearchTree<T>::swap(BinaryNode<T>* a, BinaryNode<T>* b){
    int a_key = a->key;
    a->key = b->key;
    b->key = a_key;
    T a_value = T{a->value};
    a->value = b->value;
    b->value = a_value;
};

template <typename T>
void BinarySearchTree<T>::rightRotate(BinaryNode<T>* node){
    swap(node, node->left);
    BinaryNode<T>* buffer = node->right;
    node->right = node->left;
    node->left = node->left->left;
    node->right->left = node->right->right;
    node->right->right = buffer;
    updateHeight(node->right);
    updateHeight(node->left);
};

template <typename T>
void BinarySearchTree<T>::leftRotate(BinaryNode<T>* node){
    swap(node, node->right);
    BinaryNode<T>* buffer = node->left;
    node->left = node->right;
    node->right = node->left->right;
    node->right->left = node->right->right;
    node->left->right = node->left->left;
    node->left->left = buffer;
    updateHeight(node->left);
    updateHeight(node);
};

template <typename T>
void BinarySearchTree<T>::balance(BinaryNode<T>* node){
    int balance = getBalance(node);
    if(balance == -2){
        if(getBalance(node->left) == 1) leftRotate(node->left);
        rightRotate(node);
    } else if(balance == 2){
        if(getBalance(node->right) == -1) rightRotate(node->right);
        leftRotate(node);
    }
};

template <typename T>
BinaryNode<T>* BinarySearchTree<T>::Delete(BinaryNode<T>* node, int key){
    if(node==nullptr) return nullptr;
    else if(key<node->key) node->left = Delete(node->left, key);
    else if(key>node->key) node->right = Delete(node->right, key);
    else{
        if(node->left == nullptr || node->right == nullptr){
            node = (node->left == nullptr)? node->right:node->left;
        }
        else{
            BinaryNode<T>* maxInLeft = getMax(node->left);
            node->key = maxInLeft->key;
            node->value = maxInLeft->value;
            node->right = Delete(node->right, maxInLeft->key);
        }
    }
    if(node!= nullptr){
        if (node != nullptr) {
            updateHeight(node);
            balance(node);
        }
    }
    return node;
};

template <typename T>
void BinarySearchTree<T>::PrintTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    PrintTree(node->left);
    std::cout<<node->value;
    PrintTree(node->right);
};

template <typename T>
void BinarySearchTree<T>::DeleteTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    std::cout<<node->value;
};

template <typename T>
void BinarySearchTree<T>::CopyTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    CopyTree(node->left);
    CopyTree(node->right);
    std::cout<<node->value;
};

template <typename T>
void BinarySearchTree<T>::EnQueueLeft(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node){
    if(!node->left) list.Append(node->left);
};

template <typename T>
void BinarySearchTree<T>::EnQueueRight(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node){
    if(!node->right) list.Append(node->right);
};

//public


template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
    top = new BinaryNode<T>();
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& searchTree){
    this->DeleteTree(top);

};

template <typename T>
int BinarySearchTree<T>::GetHeight(){
    return this->top->height;
};

template <typename T>
bool BinarySearchTree<T>::Contains(T item){
    if(this->Find(item)!=-1) return true;
    return false;
};

template <typename T>
void BinarySearchTree<T>::Insert(int key, const T& item) {
    this->insert(top, key, T{item});
};

template <typename T>
void BinarySearchTree<T>::Remove(T item){
    int key = this->Find(item);
    this->Delete(top, key);
};

template <typename T>
void BinarySearchTree<T>::Remove(int key){
    this->Delete(top, key);
};

template <typename T>
int BinarySearchTree<T>::Find(T item){
    BinaryNode<T>* node;
    if(node) return node->value;
    else return -1;
};

template <typename T>
T* BinarySearchTree<T>::Find(int key){
    BinaryNode<T>* node = this->search(top, key);
    if(node) return node->value;
    else return nullptr;
};

template <typename T>
T* BinarySearchTree<T>::Find(const LinkedList<PATH>& list){
    BinaryNode<T>* node;
    if(node) return node->value;
    else return nullptr;
};

//void Traverse(BinaryNode *node){
//    if(node== nullptr){ return;}
//    std::cout<<node->element;//1 pre-order
//    Traverse(node->left);
//    std::cout<<node->element;//2 in-order - отсортированный массив
//    Traverse(node->right);
//    std::cout<<node->element; //3 post-order
//}

template <typename T>
void BinarySearchTree<T>::Traverse(void (*action)(T), ORDER order){
    LinkedList<BinaryNode<T>*>* list = new LinkedList<T>();
    switch (order) {
        case PREORDER:
            list->Append(top);
            while(list->GetLength() != 0){
                BinaryNode<T>* node = list->GetLast();
                action(node->value);
                this->EnQueueRight(list, node);
                this->EnQueueRight(list, node);
            }
            break;
        case INORDER:
            this->EnQueueRight(list, top);
            list->Append(top);
            this->EnQueueLeft(list, top);
            while(list->GetLength() != 0){
                BinaryNode<T>* node = list->GetLast();
                action(node->value);
                this->EnQueueRight(list, top);
                list->Append(top);
                this->EnQueueLeft(list, top);
            }
            break;
        case POSTORDER:
            list->Append(top);
            this->EnQueueRight(list, top);
            this->EnQueueLeft(list, top);
            while(list->GetLength() != 0){
                BinaryNode<T>* node = list->GetLast();
                action(node->value);
                list->Append(top);
                this->EnQueueRight(list, top);
                this->EnQueueLeft(list, top);
            }
            break;
        default:
            break;
    }
    delete list;
};

template <typename T>
void BinarySearchTree<T>::ForEach(void (*action)(T)){
    LinkedList<BinaryNode<T>*>* list = new LinkedList<T>();
    this->EnQueueRight(list, top);
    list->Append(top);
    this->EnQueueLeft(list, top);
    while(list->GetLength() != 0){
        BinaryNode<T>* node = list->GetLast();
        action(node->value);
        this->EnQueueRight(list, node);
        this->EnQueueLeft(list, node);
    }
    delete list;
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    top->DeleteTree(top);
    delete top;
};


#endif //BINARY_SEARCH_TREE_H