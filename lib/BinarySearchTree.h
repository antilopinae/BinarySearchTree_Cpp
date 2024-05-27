//
// Created by antilopa on 23.05.24.
//

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "LinkedList.h"

enum PATH{
    LEFT, RIGHT
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
private:
    BinaryNode<T>* top;
protected:
    static BinaryNode<T>* insert(BinaryNode<T>& node, int key, T value);
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
    static void CopyTree(BinaryNode<T>* node, const BinaryNode<T>& tree);
    static bool EnQueueLeft(LinkedList<BinaryNode<T>*>* list, BinaryNode<T>* node);
    static bool EnQueueRight(LinkedList<BinaryNode<T>*>* list, BinaryNode<T>* node);
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& searchTree);
    int GetHeight();
    int GetHeight(int key);
    bool Contains(int key);
    void Insert(int key, const T& item);
    void Remove(int key);
    T* Find(int key);
    T* Find(const LinkedList<PATH>& list);
    void ForEach(void (*action)(BinaryNode<T>&));
    void Traverse(void (*action)(BinaryNode<T>&), ORDER order);
    void PrintTree();
    ~BinarySearchTree();
};


//protected


template <typename T>
BinaryNode<T>* BinarySearchTree<T>::insert(BinaryNode<T>& node, int key, T value){
    if(key<node.key){
        if(node.left == nullptr){
            node.left = new BinaryNode(key, value);
        }
        else {
            BinaryNode<T>* _node = insert(*node.left, key, value);
            updateHeight(_node);
            balance(_node);
        }
        return &node;
    }
    else if(key>=node.key){
        if(node.right == nullptr){
            node.right = new BinaryNode(key, value);
        }
        else {
            BinaryNode<T>* _node = insert(*node.right, key, value);
            updateHeight(_node);
            balance(_node);
        }
        return &node;
    }
    return nullptr;
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
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = buffer;
    updateHeight(node->right);
    updateHeight(node);
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
    updateHeight(node);
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
            node->left = Delete(node->left, maxInLeft->key);
        }
    }
    if(node!= nullptr){
        updateHeight(node);
        balance(node);
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
    delete node;
};

template <typename T>
void BinarySearchTree<T>::CopyTree(BinaryNode<T>* first, const BinaryNode<T>& tree){
    if(first == nullptr) return;

    LinkedList<BinaryNode<T>*>* list = new LinkedList<BinaryNode<T>*>();
    list->Append(tree);

    while(list->GetLength() != 0){
        BinaryNode<T>* node = list->GetLast();
        insert(first, node->key, node->value);

        list->Delete(list->GetLength()-1);
        EnQueueRight(list, node);
        EnQueueLeft(list, node);
    }
    delete list;
};

template <typename T>
bool BinarySearchTree<T>::EnQueueLeft(LinkedList<BinaryNode<T>*>* list, BinaryNode<T>* node){
    if(node->left) {
        list->Append(node->left);
        return true;
    }
    else return false;
};

template <typename T>
bool BinarySearchTree<T>::EnQueueRight(LinkedList<BinaryNode<T>*>* list, BinaryNode<T>* node){
    if(node->right) {
        list->Append(node->right);
        return true;
    }
    else return false;
};


//public


template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
    top = nullptr;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& searchTree){
    if(!top) this->DeleteTree(top);
    this->CopyTree(searchTree.top);
};

template <typename T>
int BinarySearchTree<T>::GetHeight(){
    if(top == nullptr) return 0;
    return this->top->height;
};

template <typename T>
int BinarySearchTree<T>::GetHeight(int key){
    if(top == nullptr) throw IllegalException("NullPointerException in BinarySearchTree");
    BinaryNode<T>* node = this->search(top, key);
    if(node) return node->height;
    else return -1;
};

template <typename T>
bool BinarySearchTree<T>::Contains(int key){
    if(top == nullptr) return false;
    if(this->Find(key)!= nullptr) return true;
    return false;
};

template <typename T>
void BinarySearchTree<T>::Insert(int key, const T& item) {
    if(top == nullptr) top = new BinaryNode<T>(key, T{item});
    else this->insert(*top, key, T{item});
    updateHeight(top);
    balance(top);
};

template <typename T>
void BinarySearchTree<T>::Remove(int key){
    if(top == nullptr) throw IllegalException("NullPointerException in BinarySearchTree");
    this->Delete(top, key);
};

template <typename T>
T* BinarySearchTree<T>::Find(int key){
    if(top == nullptr) return nullptr;

    BinaryNode<T>* node = this->search(top, key);
    if(node) return &node->value;
    else return nullptr;
};

template <typename T>
T* BinarySearchTree<T>::Find(const LinkedList<PATH>& list){
    if(top == nullptr) return nullptr;
    BinaryNode<T>* node = top;

    LinkedList<PATH>& _list = const_cast<LinkedList<PATH>&>(list);
    PATH path;

    for(size_t i=0; i<_list.GetLength(); ++i){
        path = _list.Get(i);
        switch (path) {
            case LEFT:
                if(node == nullptr) return nullptr;
                node = node->left;
                break;
            case RIGHT:
                if(node == nullptr) return nullptr;
                node = node->right;
                break;
            default:
                break;
        }
    }

    if(node) return &node->value;
    else return nullptr;
};

template <typename T>
void BinarySearchTree<T>::Traverse(void (*action)(BinaryNode<T>&), ORDER order){
    if(top == nullptr) return;

    LinkedList<BinaryNode<T>*>* list = new LinkedList<BinaryNode<T>*>();
    switch (order) {
//Inorder => Left, Root, Right.
//Preorder => Root, Left, Right.
//Post order => Left, Right, Root.
        case PREORDER:
            list->Append(top);
            while(list->GetLength() != 0){
                BinaryNode<T>* node = list->GetLast();
                action(*node);
                list->Delete(list->GetLength()-1);
                this->EnQueueRight(list, node);
                this->EnQueueLeft(list, node);
            }
            break;
        case INORDER:
        {
            if(top == nullptr) break;
            BinaryNode<T>* node = top;
            while(list->GetLength()!=0 || node != nullptr){
                if(node!= nullptr){
                    list->Append(node);
                    node = node->left;
                } else{
                    node = list->GetLast();
                    list->Delete(list->GetLength()-1);
                    action(*node);
                    node = node->right;
                }
            }
            break;
        }
        case POSTORDER:
        {
            BinaryNode<T>* node = top;
            LinkedList<bool>* visit = new LinkedList<bool>();
            list->Append(node);
            visit->Append(false);
            bool v;

            while(list->GetLength()!=0){
                node = list->GetLast();
                list->Delete(list->GetLength()-1);
                v = visit->GetLast();
                visit->Delete(visit->GetLength()-1);

                if(node!= nullptr){
                    if(v){
                        action(*node);
                    } else{
                        list->Append(node);
                        visit->Append(true);
                        list->Append(node->right);
                        visit->Append(false);
                        list->Append(node->left);
                        visit->Append(false);
                    }
                }
            }

            delete visit;
            break;
        }
        default:
            break;
    }
    delete list;
};

template <typename T>
void BinarySearchTree<T>::ForEach(void (*action)(BinaryNode<T>&)){
    if(top == nullptr) return;

    LinkedList<BinaryNode<T>*>* list = new LinkedList<BinaryNode<T>*>();
    list->Append(top);

    while(list->GetLength() != 0){
        BinaryNode<T>* node = list->GetLast();
        action(*node);
        list->Delete(list->GetLength()-1);

        this->EnQueueRight(list, node);
        this->EnQueueLeft(list, node);
    }
    delete list;
};

template <typename T>
void BinarySearchTree<T>::PrintTree(){
    if(top == nullptr) return;
    this->PrintTree(top);
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    if(top == nullptr) return;

    this->DeleteTree(top);
};

#endif //BINARY_SEARCH_TREE_H