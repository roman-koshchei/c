// cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CircularStack.h"

void printItem(std::optional<int> item) {
    if (item.has_value()) {
        std::cout << "value: " << item.value() << std::endl;
    }
    else {
        std::cout << "no value" << std::endl;
    }
}

int main() {
    std::cout << "Circular Stack" << std::endl;

    CircularStack<int, uint8_t> stack = CircularStack<int, uint8_t> (3);
    stack.Push(3);
    stack.Push(5);
    stack.Push(6);
    stack.Push(6);
    stack.Push(3);

    for (int i = 0; i < 8; i += 1) {
        auto item = stack.Pop();
        printItem(item);
        
        if (i == 3) {
            stack.Push(8);
        }
    }

    stack.Clear();
    stack.Push(87);
    auto item = stack.Pop();
    printItem(item);
}