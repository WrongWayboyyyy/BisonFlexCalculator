#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdlib.h>

#include "node.h"

#define DEFAULT_ARENA_SIZE 16
#define MULTIPLY_FACTOR 2

typedef struct arena_t 
{
  struct node_t* arena;
  unsigned int size;
  unsigned int allocated;
} arena_t;

// 0 - ok, !0 - failure
extern int arena_construct (arena_t* arena); 
extern void arena_free (arena_t* arena); 
// -1 - failure, index in arena otherwise
extern int arena_allocate (arena_t* arena, unsigned int count); 
extern void arena_clear (arena_t* arena);

#endif /* _ARENA_H_ */