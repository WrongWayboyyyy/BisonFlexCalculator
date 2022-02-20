#ifndef _NODE_H_
#define _NODE_H_

typedef struct bin_op_t {
    unsigned int l;
    unsigned int r;
} bin_op_t;

typedef struct node_t {
    union {
        double val;
        bin_op_t op;
    };
    int nodetype;
} node_t;



typedef struct value_t {
    int nodetype;
    double number;
} value_t;


#endif