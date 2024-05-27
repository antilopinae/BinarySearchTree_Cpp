//
// Created by antilopa on 13.05.24.
//

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <string>
#include "BinarySearchTree.h"

template<typename T>
void printItem(T& item){
    std::cout<<item<<std::endl;
}

template<typename T>
void testQueueWithInput(BinarySearchTree<T>* binaryTree) {
    char choice;
    T item;
    int key;
    do {
        std::cout << "Choose an operation:\n";
        std::cout << "1. Append by key\n";
        std::cout << "2. Remove by key\n";
        std::cout << "3. Contains by key\n";
        std::cout << "4. Get Height by key\n";
        std::cout << "5. Find by key\n";
        std::cout << "6. Print Traverse PRE-ORDER\n";
        std::cout << "7. Print Traverse IN-ORDER\n";
        std::cout << "8. Print Traverse POST-ORDER\n";

        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1': //append
                std::cout << "Enter item to append: ";
                std::cin >> item;
                std::cout << "Enter key to this item " << item << ": ";
                std::cin >> key;
                binaryTree->Insert(key,item);
                break;
            case '2': //remove
                if (binaryTree->GetHeight() > 0) {
                    std::cout << "Enter key to remove: ";
                    std::cin >> key;
                    if(binaryTree->Contains(key)){
                        binaryTree->Remove(key);
                    }else{
                        std::cout << "No such item with this key in tree." << std::endl;
                    }
                } else {
                    std::cout << "Binary Tree is empty." << std::endl;
                }
                break;
            case '3': //contains
                std::cout << "Enter key to check: ";
                std::cin >> key;
                if(binaryTree->Contains(key)){
                    std::cout << "There is item with this key in tree." << std::endl;
                }else{
                    std::cout << "No such item with this key in tree." << std::endl;
                }
                break;
            case '4': //height
                std::cout << "Enter key to item: ";
                std::cin >> key;
                if(binaryTree->Contains(key)){
                    std::cout << binaryTree->GetHeight(key) << std::endl;
                }else{
                    std::cout << "No such item with this key in tree." << std::endl;
                }
                break;
            case '5': //find
            {
                std::cout << "Enter key to find item: ";
                std::cin >> key;
                T* _item = binaryTree->Find(key);
                if(_item){
                    std::cout << *_item << std::endl;
                }else{
                    std::cout << "No such item with this key in tree." << std::endl;
                }
                break;
            }
            case '6': //print preorder
                binaryTree->Traverse(&printItem<T>,PREORDER);
                std::cout<<std::endl;
                break;
            case '7': //print inorder
                binaryTree->Traverse(&printItem<T>,INORDER);
                std::cout<<std::endl;
                break;
            case '8': //print postorder
                binaryTree->Traverse(&printItem<T>,POSTORDER);
                std::cout<<std::endl;
                break;
            case '9': //exit
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
                binaryTree->PrintTree();
                std::cout<<"Print Tree"<<std::endl;
                binaryTree->ForEach(printItem<T>);
                std::cout<<"For Each"<<std::endl;
                break;
        }
    } while (choice != '9');
}

int debug() {
    BinarySearchTree<int>* intTree = new BinarySearchTree<int>();
    std::cout << "Testing binary search tree:\n" << std::endl;
    testQueueWithInput<int>(intTree);
    delete intTree;
    return 0;
}

#endif //DEBUGGING_H
