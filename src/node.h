#ifndef _NODE_H_
#define _NODE_H_

#include "value.h"

typedef struct bin_op_t 
{
  unsigned int l;
  unsigned int r;
} bin_op_t;

typedef struct node_t 
{
  union 
  {
    value_type_t val;
    bin_op_t op;
  };
  int nodetype;
} node_t;

#endif /* _NODE_H_ */