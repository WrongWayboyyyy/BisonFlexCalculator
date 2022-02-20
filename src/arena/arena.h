#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdlib.h>
#include "ast.h"
#include "node.h"

#define DEFAULT_ARENA_SIZE 16
#define MULTIPLY_FACTOR 2

typedef struct arena_t {
    struct node_t* arena;
    unsigned int size;
    unsigned int allocated;
} arena_t;

extern int arena_construct (arena_t* arena); // 0 - ok, !0 - failure
extern void arena_free (arena_t* arena); 
extern int arena_allocate (arena_t* arena, unsigned int count); // -1 - failure, index in arena otherwise
extern void arena_clear (arena_t* arena);

#endif /* _ARENA_H_ */