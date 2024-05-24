//
// Created by antilopa on 13.05.24.
//

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <string>
#include "BinarySearchTree.h"

template<class T>
void testQueueWithInput(BinarySearchTree<T>* binaryTree) {
    char choice;
    T item;

    do {
        std::cout << "Choose an operation:\n";
        std::cout << "1. Push\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Get Length\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter item to push: ";
                std::cin >> item;
                binaryTree->Push(item);
                break;
            case '2':
                if (binaryTree->GetLength() > 0) {
                    std::cout << "Popped: " << binaryTree->Pull() << std::endl;
                } else {
                    std::cout << "Queue is empty." << std::endl;
                }
                break;
            case '3':
                std::cout << "Queue Length: " << binaryTree->GetLength() << std::endl;
                break;
            case '4':
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while (choice != '4');
}

int debug() {
    BinarySearchTree<int>* intTree = new BinarySearchTree<int>();
    std::cout << "Testing integer queue:\n" << std::endl;
    testQueueWithInput(intTree);

    return 0;
}

#endif //DEBUGGING_H
