#ifndef BI_LIST_CPP
#define BI_LIST_CPP

#include "bi_list.h"
#include <iostream>

BiList::BiList() {
    this->front = nullptr;
    this->back = nullptr;
}

BiList::~BiList() {
    this->clear();
}

void BiList::clear() {
    if (this->front == nullptr) return;

    BiNode* current = this->front;
    while (current != nullptr) {
        BiNode* next = current->next;
        delete current;
        current = next;
    }

    this->front = nullptr;
    this->back = nullptr;
}

BiNode* BiList::get_front() {
    return this->front;
}

BiNode* BiList::get_back() {
    return this->back;
}

void BiList::push_back(int value) {
    BiNode* node = new BiNode(value);
    if (this->back == nullptr) {
        this->front = node;
        this->back = node;
    }
    else {
        this->back->next = node;
        node->prev = this->back;
        this->back = node;
    }
}

void BiList::push_front(int value) {
    BiNode* node = new BiNode(value);
    if (this->front == nullptr) {
        this->front = node;
        this->back = node;
    }
    else {
        node->next = this->front;
        this->front->prev = node;
        this->front = node;
    }
}

void BiList::insert(int value, BiNode* node) {
    BiNode* current = this->front;
    while (current != nullptr) {
        if (current == node) {
            // node actually exists in this list
            BiNode* new_node = new BiNode(value);

            if (current->prev == nullptr) {
                // front
                new_node->next = current;
                current->prev = new_node;
                this->front = new_node;
            }
            else {
                new_node->prev = current->prev;
                new_node->next = current;
                current->prev->next = new_node;
                current->prev = new_node;
            }

            return;
        }
    }
}

void BiList::insert(BiNode* node, int value) {
    BiNode* current = this->front;
    while (current != nullptr) {
        if (current == node) {
            // node actually exists in this list
            BiNode* new_node = new BiNode(value);

            if (current->next == nullptr) {
                // back
                new_node->prev = current;
                current->next = new_node;
                this->back = new_node;
            }
            else {
                new_node->prev = current;
                new_node->next = current->next;
                current->next->prev = new_node;
                current->next = new_node;
            }

            return;
        }
    }
}

void BiList::remove(int value) {
    if (this->front == nullptr) {
        // there are no elements in list
        return;
    }

    if (this->front == this->back) {
        // there is only 1 element in list
        if (this->front->data == value) {
            delete this->front;
            this->front = nullptr;
            this->back = nullptr;
        }
        return;
    }

    // now in the list at least 2 elements
    BiNode* current = this->front;
    while (current != nullptr) {
        if (current->data == value) {
            if (current->prev == nullptr) {
                // current == front
                this->front = current->next;
                delete current;
            }
            else if (current->next == nullptr) {
                // current == back
                this->back = current->prev;
                delete current;
            }
            else {
                // current is somewhere in between
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            return;
        }
        current = current->next;
    }
}

void BiList::forward_view() {
    BiNode* current = this->front;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void BiList::reverse_view() {
    BiNode* current = this->back;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}

BiNode* BiList::find(int value) {
    BiNode* current = this->front;
    while (current != nullptr) {
        if (current->data == value) return current;
    }
    return nullptr;
}

/// <summary>
/// Method assumes that nodes actually exist in list
/// </summary>
void BiList::swap(BiNode* node1, BiNode* node2) {
    if (node1 == node2) return;

    BiNode* prev1 = node1->prev;
    BiNode* next1 = node1->next;
    BiNode* prev2 = node2->prev;
    BiNode* next2 = node2->next;

    if (next1 == node2) {
        // -> node1 -> node2 ->
        node1->next = next2;
        node1->prev = node2;
        node2->next = node1;
        node2->prev = prev1;
        if (next2 != nullptr) next2->prev = node1;
        if (prev1 != nullptr) prev1->next = node2;
    }
    else if (next2 == node1) {
        // -> node2 -> node1 ->
        node2->next = next1;
        node2->prev = node1;
        node1->next = node2;
        node1->prev = prev2;
        if (next1 != nullptr) next1->prev = node2;
        if (prev2 != nullptr) prev2->next = node1;
    }
    else {
        // -> node1 -> ... -> node2 ->
        // -> node2 -> ... -> node2 ->
        node1->next = next2;
        node1->prev = prev2;
        node2->next = next1;
        node2->prev = prev1;
        if (next1 != nullptr) next1->prev = node2;
        if (prev1 != nullptr) prev1->next = node2;
        if (next2 != nullptr) next2->prev = node1;
        if (prev2 != nullptr) prev2->next = node1;
    }

    // Update the front and back pointers
    if (node1->prev == nullptr) this->front = node1;
    if (node2->prev == nullptr) this->front = node2;
    if (node1->next == nullptr) this->back = node1;
    if (node2->next == nullptr) this->back = node2;
}

void BiList::sort() {
    for (BiNode* i = this->front; i != nullptr; i = i->next) {
        BiNode* min = i;
        for (BiNode* j = i->next; j != nullptr; j = j->next) {
            if (j->data < min->data) {
                min = j;
            }
        }
        if (min != i) {
            this->swap(i, min);
            // Swap will invalidate the iterator 'i', so we need to reset it
            i = min;
        }
    }
}

#endif