#include <stdio.h>
#include "int_vector.h"
#include "voidfnptr_vector.h"

void wat() {
    printf("wat\n");
}

int main() {
    int_vector vec;
    int_vector_new_empty(&vec);

    int_vector_push_back(&vec, 42);
    int_vector_push_back(&vec, 13);
    int_vector_push_back(&vec, 12);
    int_vector_push_back(&vec, 4);

    for (size_t i = 0; i < vec.size; i++) {
        printf("vec[%zd] = %d\n", i, vec.data[i]);
    }

    // copying a vector
    int_vector vec2;
    int_vector_new_copy(&vec2, &vec);

    // deleting both
    int_vector_delete(&vec);
    int_vector_delete(&vec2);

    // void function pointer vector example
    voidfnptr_vector lolvec;
    voidfnptr_vector_new_empty(&lolvec);

    voidfnptr_vector_push_back(&lolvec, &wat);
    lolvec.data[0]();

    voidfnptr_vector_delete(&lolvec);

    // creating an impossibly large vector
    int_vector vec3;
    int_vector_new_empty(&vec3);
    int_vector_reserve(&vec3, 1024ULL * 1024ULL * 1024ULL * 1024ULL);
    int_vector_delete(&vec3);
}
