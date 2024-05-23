#ifndef BI_LIST_H
#define BI_LIST_H

#include "bi_node.h"

struct BiList {
private:
    BiNode* front;
    BiNode* back;

public:
    BiList();
    ~BiList();

    BiNode* get_back();
    BiNode* get_front();

    void clear();
    void push_back(int value);
    void push_front(int value);
    void insert(int value, BiNode* node);
    void insert(BiNode* node, int value);
    void remove(int value);
    void forward_view();
    void reverse_view();
    BiNode* find(int value);

    void swap(BiNode* node1, BiNode* node2);
    void sort();
};

#endif
