#include "arena.h"
#include <stdio.h>

int main() {
    struct arena a;
    arena_construct(&a);
    int* num;
    for (int i = 0; i < 1000 * 1000; ++i) {
        num = (int*) &a.arena[arena_allocate(&a, sizeof(int))];
    }
    *num = 3;
    printf("%d", *num);
}