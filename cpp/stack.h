#ifndef STACK_H
#define STACK_H

#include "node.h"
#include "optional.h"

struct Stack {
private:
    Node* head;

public:
    Stack();
    ~Stack();

    void push(int value);
    void push(Stack* another_stack);
    void pop();

    /// <returns>Optional int, because stack can be empty</returns>
    Optional<int> top() const;

    bool empty() const;
    void view() const;
};

#endif
