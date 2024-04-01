#ifndef STACK_H
#define STACK_H

#include "stdlib.h"

#define CONCAT(a, b) a##b

#define STACK(type) CONCAT(type, Stack)

#define STACK_NODE(type) struct type##StackNode \

#define DEFINE_STACK(type) \
    typedef struct type##StackNode type##StackNode; \
    struct type##StackNode { \
        type##StackNode* next; \
        type value; \
    }; \
    \
    typedef struct type##Stack { \
        type##StackNode* head; \
    } type##Stack; \
    bool type##_stack_pop(struct type##Stack* stack, type* value) { \
            if (stack->head == NULL) { \
                return false; \
            } \
            \
            *value = stack->head->value; \
            \
            type##StackNode* next = stack->head->next; \
            free(stack->head); \
            stack->head = next; \
            \
            return true; \
        }; \

#define STACK_NEW(type) (struct type##Stack) { NULL }

#define STACK_FREE(type, stack) \
    do { \
        if ((stack).head != NULL) { \
            type##StackNode* current = (stack).head; \
            while(current != NULL) { \
                type##StackNode* next = current->next; \
                free(current); \
                current = next; \
            } \
            (stack).head = NULL; \
        } \
    } while (0) \

#define STACK_PUSH(type, stack, item) \
    do { \
        type##StackNode* node = (type##StackNode*) malloc(sizeof(type##StackNode)); \
        assert(node != NULL); \
        node->value = (type) item; \
        node->next = (stack).head; \
        (stack).head = node; \
    } while (0) \

#define STACK_POP(type, stack, result) (type##_stack_pop(stack, result))

#endif
