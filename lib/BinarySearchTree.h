//
// Created by antilopa on 23.05.24.
//

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "LinkedList.h"

template <typename T>
struct BinaryNode{
    int key;
    T value;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
    int height = 0;
    BinaryNode(int key, T value){ this->key = key; this->value = value;}
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
    static void EnQueue(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node);
};

template <typename T>
void BinaryNode<T>::insert(BinaryNode<T>& node, int key, T value){
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
BinaryNode<T>* BinaryNode<T>::search(BinaryNode<T>* node, int key){
    if(node == nullptr) return nullptr;
    if(node->key == key) return node;
    return (key<node->key)?search(node->left, key):search(node->right, key);
};

template <typename T>
BinaryNode<T>* BinaryNode<T>::getMin(BinaryNode<T>* node){
    if(node == nullptr) return nullptr;
    if(node->left == nullptr) return node;
    return getMin(node->left);
};

template <typename T>
BinaryNode<T>* BinaryNode<T>::getMax(BinaryNode<T>* node){
    if(node == nullptr) return nullptr;
    if(node->right == nullptr) return node;
    return getMax(node->right);
};

template <typename T>
int BinaryNode<T>::getHeight(BinaryNode<T>* node){
    return node== nullptr?-1:node->height;
};

template <typename T>
void BinaryNode<T>::updateHeight(BinaryNode<T>* node){
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    node->height = ((leftHeight>rightHeight)?leftHeight:rightHeight)+1;
};

template <typename T>
int BinaryNode<T>::getBalance(BinaryNode<T>* node){
    return (node == nullptr)?0: getHeight(node->right) - getHeight(node->left);
};

template <typename T>
void BinaryNode<T>::swap(BinaryNode<T>* a, BinaryNode<T>* b){
    int a_key = a->key;
    a->key = b->key;
    b->key = a_key;
    T a_value = T{a->value};
    a->value = b->value;
    b->value = a_value;
};

template <typename T>
void BinaryNode<T>::rightRotate(BinaryNode<T>* node){
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
void BinaryNode<T>::leftRotate(BinaryNode<T>* node){
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
void BinaryNode<T>::balance(BinaryNode<T>* node){
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
BinaryNode<T>* BinaryNode<T>::Delete(BinaryNode<T>* node, int key){
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
void BinaryNode<T>::PrintTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    PrintTree(node->left);
    std::cout<<node->value;
    PrintTree(node->right);
};

template <typename T>
void BinaryNode<T>::DeleteTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    std::cout<<node->value;
};

template <typename T>
void BinaryNode<T>::CopyTree(BinaryNode<T>* node){
    if(node == nullptr) return;
    CopyTree(node->left);
    CopyTree(node->right);
    std::cout<<node->value;
};

template <typename T>
void BinaryNode<T>::EnQueue(LinkedList<BinaryNode<T>*>& list, BinaryNode<T>* node){
    list.Append(node->left);
    list.Append(node->right);
};




template <typename T>
class BinarySearchTree{
private:
    BinaryNode<T>* top = new BinaryNode<T>();
protected:
    void AddTo(BinaryNode<T>* node, T item);
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& searchTree);
    int GetHeight();
    bool Contains(T item);
    void Add(T item);
    void Remove(T item);
    void ForEach(void (*action)(T));
    void Insert(int key, T item);
    ~BinarySearchTree();
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(){

};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& searchTree){

};

template <typename T>
void BinarySearchTree<T>::ForEach(void (*action)(T)){
    LinkedList<BinaryNode<T>*>* list = new LinkedList<T>();
    top->EnQueue(list, top);
    while(list->GetLength() != 0){
        BinaryNode<T>* node = list->GetLast();
        action(node->value);
        top->EnQueue(list, top);
    }
    delete list;
};

template <typename T>
void BinarySearchTree<T>::Insert(int key, T item) {
    top->insert(top, key, item)
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    top->DeleteTree(top);
    delete top;
};

//bool Find(BinaryNode * node, int value){
//    if(node== nullptr){ return false;}
//    if(node->element == value){ return true;}
//    if(node->element>value){ return Find(node->left, value);}
//    return Find(node->right, value);
//}
//
//bool Insert(BinaryNode * node, int value){
//    if(node == nullptr){ return false; }//подвешиваем новый ptr
//    if(node->element == value){ return true;}
//    if(node->element>value){ return Find(node->left, value);}
//    return Find(node->right, value);
//}
//
////удаляемый элемент бездетный - просто удаляем
////удаляемый элемент имеет 1 ребенка - связываем родителя удаляемого элементы и его ребенка
//
//void Erase(){
//    //1.найти элемент больший данного (один шаг влево,
//    //один шаг вправо и влево до упора)
//    //2.у найденного узла не больше одного ребенка - свапаем значение
//    // и удаляем (либо сл.1 или 2)

//}
//
//void Traverse(BinaryNode *node){
//    if(node== nullptr){ return;}
//    std::cout<<node->element;//1 pre-order
//    Traverse(node->left);
//    std::cout<<node->element;//2 in-order - отсортированный массив
//    Traverse(node->right);
//    std::cout<<node->element; //3 post-order
//}

#endif //BINARY_SEARCH_TREE_H
