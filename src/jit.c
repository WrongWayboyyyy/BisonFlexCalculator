#include "jit.h"


#define CALC_ADD(TOP, L, R) TOP {               \
    TOP =                                       \

}
#define CALC_SUB(TOP, L, R) TOP
#define CALC_MUL(TOP, L, R) TOP
#define CALC_DIV(TOP, L, R) TOP
#define CALC_ABS(TOP, ARG) TOP
#define CALC_NEG(TOP, ARG) TOP
#define CALC_NUM(TOP, ARG) TOP {                \
    TOP = LLVMConstInt(LLVMInt32Type(), ARG);   \
}
#define CALC_RESULT(TOP) eval(arena) 