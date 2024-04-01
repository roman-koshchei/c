#include "stdio.h"
#include "vec.h"
#include "queue.h"
#include "stack/point_stack.h"
#include "stack/stack.h"

// Present examples for all data structures

typedef struct {
    int x;
} Example;

STACK_DEFINE_FOR(Example);
VEC_DEFINE_FOR(Example);
QUEUE_DEFINE_FOR(Example);

void print_example(Example value) {
    printf("example x=%d\n", value.x);
}

void stack_example_operations(ExampleStack* stack) {
    STACK_PUSH(Example, *stack, { 4 });
    STACK_PUSH(Example, *stack, { 5 });
    STACK_PUSH(Example, *stack, { 6 });

    STACK_NODE(Example)* iter = stack->head;
    while (iter != NULL) {
        print_example(iter->value);
        iter = iter->next;
    }

    printf("\n");

    for (int i = 0; i < 4; i += 1) {
        Example value;
        if (STACK_POP(Example, stack, &value)) {
            printf("poped ");
            print_example(value);
        }
        else {
            printf("nothing to pop\n");
        }
    }
}

void stack_example() {
    STACK(Example) stack = STACK_NEW(Example);

    stack_example_operations(&stack);

    STACK_FREE(Example, stack);
}

void process_vec(VEC(Example)* vector) {
    VEC_PUSH(*vector, (Example) { 1 });
    VEC_PUSH(*vector, (Example) { 2 });
    VEC_PUSH(*vector, (Example) { 3 });

    for (int i = 0; i < vector->size; i += 1) {
        printf("pushed to vector: ");
        print_example(vector->data[i]);
    }

    VEC_REMOVE(*vector, 1);
    printf("removed element with index 1 from vector\n");

    for (int i = 0; i < vector->size; i += 1) {
        print_example(vector->data[i]);
    }
}

void vec_example() {
    VEC(Example) vector = VEC_NEW(Example, 2);

    process_vec(&vector);

    VEC_FREE(vector);
}

int main() {
    stack_example();

    printf("\n");

    vec_example();

    return 0;
}