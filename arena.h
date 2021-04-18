#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdlib.h>
#include "structure.h"

#define DEFAULT_ARR_SIZE 4
#define MULTIPLY_FACTOR 2

typedef struct arena {
    char* arena;
    unsigned int size;
    unsigned int allocated;
} arena;

extern int arena_construct(arena* arena); // 0 - ok, !0 - failure
extern void arena_free(arena* arena); 
extern int arena_allocate(arena* arena, unsigned int count); // -1 - failure, index in arena otherwise

#endif /* _ARENA_H_ */