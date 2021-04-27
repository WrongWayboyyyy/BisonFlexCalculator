#include "arena.h"

#define DEFAULT_ARENA_SIZE 16
#define MULTIPLY_FACTOR 2

int arena_construct (arena* arena) {
    arena->size = DEFAULT_ARENA_SIZE;
    arena->allocated = 0;
    arena->arena = malloc(sizeof(node) * arena->size);
    if (arena->arena == NULL) {
        return (!0);
    }
    return 0;
}

void arena_free (arena* arena) {
    struct arena* newArena;
    if (arena->arena != NULL)
        free(arena->arena);
    arena->arena = NULL;
}

int arena_allocate (arena* arena, unsigned int count) {
    if (arena->allocated + count >= arena->size) {
        unsigned int newSize = MULTIPLY_FACTOR * arena->size;
        node* newArena = realloc(arena->arena, newSize * sizeof(node));
        if (NULL == newArena) {
            return -1;
        }
        arena->arena = newArena;
        arena->size = newSize;
    }
    unsigned int result = arena->allocated;
    arena->allocated += count;
    return result;
}

