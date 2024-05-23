#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"
#include "optional.h"

struct Queue {
private:
    Node* head;
    Node* tail;

public:
    Queue();
    ~Queue();
    void enqueue(int value);
    void enqueue(Queue* another_queue);
    void dequeue();
    Optional<int> first();
    Optional<int> last();
    bool empty();
    void view();
};

#endif
