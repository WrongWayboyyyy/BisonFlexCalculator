#include "carena.h"

int allocate_node(arena* arena) {
    return arena_allocate(arena, sizeof(node));
}