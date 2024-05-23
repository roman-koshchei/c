#ifndef BI_NODE_H
#define BI_NODE_H

struct BiNode {
    int data;
    BiNode* prev;
    BiNode* next;

    BiNode(int data);
};

#endif