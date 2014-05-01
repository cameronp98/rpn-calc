#ifndef RPN_H
#define RPN_H

#include "stack.h"
#include "opmap.h"

#define isfloatc(c) (isdigit(c) || (c) == '.')

opmap_t *operations;

void rpn_init(void);
void rpn_performOperation(stack_t *stack, char operation_char);
void rpn_addOperation(char symbol, cbptr *callback);

stack_t *rpn_eval(char *expression);

#endif
