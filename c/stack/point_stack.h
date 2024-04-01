#ifndef R_STACK_H
#define R_STACK_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "assert.h"

// TODO:
// - [ ] implement stack for Point struct
// - [ ] implement generic stack
//
// Stack data structure
// Data is stored in linked list like style
//
// First in last out

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct OptionalPoint {
    bool present;
    Point val;
} OptionalPoint;

typedef struct StackNode StackNode;

struct StackNode {
    Point value;
    StackNode* next;
};

typedef struct Stack {
    StackNode* head;
} Stack;

Stack stack_new() {
    return (Stack) { NULL };
}

void stack_free(Stack* stack) {
    if (stack->head == NULL) return;

    StackNode* current = stack->head;
    while (current != NULL) {
        StackNode* next = current->next;
        free(current);
        current = next;
    }

    stack->head = NULL;
}

void stack_push(Stack* stack, Point p) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    assert(node != NULL);

    node->value = p;
    node->next = stack->head;
    stack->head = node;
}

OptionalPoint stack_pop(Stack* stack) {
    if (stack->head == NULL) {
        return (OptionalPoint) { false };
    }

    OptionalPoint point = { true };
    point.val = stack->head->value;

    StackNode* next = stack->head->next;
    free(stack->head);
    stack->head = next;

    return point;
}

bool stack_try_pop(Stack* stack, Point* value) {
    if (stack->head == NULL) {
        return false;
    }

    *value = stack->head->value;

    StackNode* next = stack->head->next;
    free(stack->head);
    stack->head = next;

    return true;
}

void stack_print(Stack stack) {
    printf("Stack from last pushed element\n");
    StackNode* iter = stack.head;
    while (iter != NULL) {
        printf("point x=%d y=%d\n", iter->value.x, iter->value.y);
        iter = iter->next;
    }
}

void point_stack_example() {
    Stack stack = stack_new();

    stack_push(&stack, (Point) { 3, 4 });
    stack_push(&stack, (Point) { 5, 6 });
    stack_push(&stack, (Point) { 7, 8 });

    stack_print(stack);

    printf("\n");

    //for (int i = 0; i < 4; i += 1) {
    //    OptionalPoint point = stack_pop(&stack);
    //    if (point.present) {
    //        printf("poped x=%d y=%d\n", point.val.x, point.val.y);
    //    }
    //    else {
    //        printf("nothing to pop\n");
    //    }
    //}

    for (int i = 0; i < 4; i += 1) {
        Point point;
        bool present = stack_try_pop(&stack, &point);

        if (present) {
            printf("poped x=%d y=%d\n", point.x, point.y);
        }
        else {
            printf("nothing to pop\n");
        }
    }

    stack_free(&stack);
}

#endif