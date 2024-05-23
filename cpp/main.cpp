// cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "stack.h"
#include "queue.h"

int main() {
    std::cout << "Hello World!\n";

    Stack stack = Stack();
    stack.push(3);
    stack.push(5);
    stack.push(6);
    stack.push(6);

    stack.view();

    stack.pop();
    stack.pop();

    stack.view();

    Queue queue = Queue();
    queue.enqueue(4);
    queue.enqueue(8);
    queue.enqueue(7);

    queue.view();

    auto first = queue.first();
    if (first.has_value()) {
        std::cout << "Has value: " << first.get_value() << std::endl;
    }
    else {
        std::cout << "No value" << std::endl;
    }

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();

    queue.view();

    first = queue.first();
    if (first.has_value()) {
        std::cout << "Has value: " << first.get_value() << std::endl;
    }
    else {
        std::cout << "No value" << std::endl;
    }
}