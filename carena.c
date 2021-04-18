#include "carena.h"

int allocate_nodes(arena* arena, unsigned int cnt) {
    return arena_allocate(arena, cnt * sizeof(node));
}