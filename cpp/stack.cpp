#ifndef STACK_CPP
#define STACK_CPP

#include "stack.h"
#include <iostream>

Stack::Stack() {
    this->head = nullptr;
}

Stack::~Stack() {
    if (this->head == nullptr) return;

    Node* current = this->head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    this->head = nullptr;
}

void Stack::push(int value) {
    Node* node = new Node(value);
    node->next = this->head;
    this->head = node;
}

void Stack::pop() {
    if (this->head == nullptr) return;

    Node* next = this->head->next;
    delete this->head;
    this->head = next;
}

Optional<int> Stack::top() const {
    if (this->head == nullptr) return Optional<int>();
    return Optional<int>(this->head->data);
}

bool Stack::empty() const {
    return this->head == nullptr;
}

void Stack::view() const {
    Node* current = this->head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void Stack::push(Stack* another_stack) {
    this->head = another_stack->head;
    another_stack->head = nullptr;
}

#endif 