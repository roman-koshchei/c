#ifndef QUEUE_H
#define QUEUE_H

#include "stdlib.h"
#include "stdbool.h"

#define CONCAT(a, b) a##b

#define QUEUE(type) CONCAT(type, Queue)

#define QUEUE_DEFINE_FOR(type) \
    typedef struct type##QueueNode type##QueueNode; \
    struct type##QueueNode { \
        type value; \
        type##QueueNode* next; \
    }; \
    typedef struct type##Queue { \
        type##QueueNode* start; \
        type##QueueNode* end; \
    } type##Queue; \
    \
    bool type##_queue_dequeue(type##Queue* queue, type* result) { \
        if(queue->start == NULL) return false; \
        *result = queue->start->value; \
        if(queue->start == queue->end) { \
            free(queue->start); \
            queue->start = NULL;\
            queue->end = NULL;\
        } else { \
            type##QueueNode* next = queue->start->next; \
            free(queue->start); \
            queue->start = next; \
        } \
        return true; \
    } \

#define QUEUE_NEW(type) (struct type##Queue) { NULL, NULL }; \

#define QUEUE_FREE(queue) \
    do { \
        while((queue).start != NULL) { \
            (queue).end = (queue).start->next; \
            free((queue).start); \
            (queue).start = (queue).end; \
        }\
        (queue).start = NULL; \
        (queue).end = NULL; \
    } while(0) \

#define QUEUE_ENQUEUE(type, queue, item) \
    do { \
        if((queue).start == NULL) { \
            (queue).start = (type##QueueNode*) malloc(sizeof(type##QueueNode)); \
            (queue).end = (queue).start; \
        } \
        else { \
            type##QueueNode node = (type##QueueNode*) malloc(sizeof(type##QueueNode)); \
            (queue).end->next = node; \
            (queue).end = node; \
        } \
    } while (0) \

#define QUEUE_DEQUEUE(type, queue_ptr, result_ptr) type##_queue_dequeue(queue_ptr, result_ptr)

#endif