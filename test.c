#include "arena.h"
#include <stdio.h>

int main() {
    struct arena a;
    printf("%d", 12);
    arena_construct(&a);
    int* num;
    for (int i = 0; i < 1; ++i) {
        num = a.arena[arena_allocate(&a, sizeof(int))];
    }
    printf("%d", *num);
}