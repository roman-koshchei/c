#ifndef BI_NODE_CPP
#define BI_NODE_CPP

#include "bi_node.h"

BiNode::BiNode(int data) {
    this->data = data;
    this->prev = nullptr;
    this->next = nullptr;
}

#endif