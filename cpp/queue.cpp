#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "queue.h"
#include <iostream>

Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
}

Queue::~Queue() {
    while (this->head != nullptr) {
        this->tail = this->head->next;
        delete this->head;
        this->head = this->tail;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

void Queue::enqueue(int value) {
    Node* node = new Node(value);
    if (this->head == nullptr) {
        this->head = node;
        this->tail = node;
    }
    else {
        this->tail->next = node;
        this->tail = node;
    }
}

void Queue::enqueue(Queue* another_queue) {
    this->head = another_queue->head;
    this->tail = another_queue->tail;
    another_queue->head = nullptr;
    another_queue->tail = nullptr;
}

void Queue::dequeue() {
    if (this->head == nullptr) return;

    if (this->head == this->tail) {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    else {
        Node* next = this->head->next;
        delete this->head;
        this->head = next;
    }
}

Optional<int> Queue::first() {
    if (this->head == nullptr) return Optional<int>();
    return Optional<int>(this->head->data);
}

Optional<int> Queue::last() {
    if (this->tail == nullptr) return Optional<int>();
    return Optional<int>(this->tail->data);
}

bool Queue::empty() {
    return this->head == nullptr;
}

void Queue::view() {
    Node* current = this->head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif