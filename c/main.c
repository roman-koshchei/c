#include "stdio.h"
#include "vec.h"

typedef struct Field {
    int num;
} Field;

typedef VEC(Field) FieldVec;

void print_field_vec(const FieldVec fields) {
    for (int i = 0; i < fields.size; i += 1) {
        printf("%d ", fields.data[i].num);
    }
    printf("\n");
}

void change_vec(FieldVec* vec) {
    VEC_PUSH(*vec, (Field) { -1 });
}

int main() {
    FieldVec fields = VEC_NEW(Field, 1);

    Field new_field = { 1 };
    VEC_PUSH(fields, new_field);

    VEC_PUSH(fields, (Field) { 10 });

    print_field_vec(fields);

    VEC_REMOVE(fields, 0);
    print_field_vec(fields);

    change_vec(&fields);
    print_field_vec(fields);

    VEC_FREE(fields);

    return 0;
}