#ifndef _NODE_H_
#define _NODE_H_

typedef struct bin_op {
    unsigned int l;
    unsigned int r;
} bin_op;

typedef struct node {
    union {
        double val;
        bin_op op;
    };
    int nodetype;
} node;



typedef struct value {
    int nodetype;
    double number;
} value;


#endif