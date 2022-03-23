#include "arena.h"

int arena_construct (arena_t* arena) {
    arena->size = DEFAULT_ARENA_SIZE;
    arena->allocated = 0;
    arena->arena = malloc (sizeof(node_t) * DEFAULT_ARENA_SIZE);
    if (arena->arena == NULL) {
        return (!0);
    }
    return 0;
}

void arena_free (arena_t *arena) {
    if (arena->arena != NULL)
        free (arena->arena);
    arena->arena = NULL;
}

void arena_clear (arena_t *arena) {
    arena->allocated = 0;
}

int arena_allocate (arena_t *arena, unsigned int count) {
    if (arena->allocated + count >= arena->size) {
        unsigned int new_size = MULTIPLY_FACTOR * arena->size;
        node_t *new_arena = realloc (arena->arena, new_size  * sizeof(node_t));
        if (NULL == new_arena) {
            return -1;
        }
        arena->arena = new_arena;
        arena->size = new_size;
    }
    unsigned int result = arena->allocated;
    arena->allocated += count;
    return result;
}

