extern int yylineno;

void yyerror(char* s);

struct Node {
    int nodetype;
    struct Node* l;
    struct Node* r;
};

struct Value {
    int nodetype;
    double number;
};

struct Node* newast(int nodetype, struct Node* l, struct Node* r);
struct Node* newnum(double d);

double eval(struct Node*);

void treefree(struct Node*);