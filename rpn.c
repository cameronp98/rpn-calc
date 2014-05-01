#include "rpn.h"

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define isfloatc(c) (isdigit(c) || (c) == '.')

float _add(float l, float r) { return l + r; }
float _sub(float l, float r) { return l - r; }
float _mul(float l, float r) { return l * r; }
float _div(float l, float r) { return l / r; }
float _pow(float l, float r) { return pow(l, r); }

opmap_t *operations;

void rpn_addOperation(char op, cbptr *func) {
    opmap_addMap(operations, op, func);
}

void rpn_init(void) {
    if (operations)
        return;

    operations = opmap_new(5);

    rpn_addOperation('+', _add);
    rpn_addOperation('-', _sub);
    rpn_addOperation('*', _mul);
    rpn_addOperation('/', _div);
    rpn_addOperation('^', _pow);
}

void rpn_performOperation(stack_t *stack, char op) {
    cbptr* callback = opmap_getFuncBySymbol(operations, op);
    if (callback == NULL) {
        printf("unknown operation '%c'\n", op);
        return;
    }

    if (stack->size < 2) {
        printf("expected 2 operands for '%c'\n", op);
        return;
    }

    float right = stack_pop(stack);
    float left = stack_pop(stack);

    stack_put(stack, callback(left, right));
}

void rpn_showResults(stack_t *results) {
    for (int i = 0 ; i < results->size; i++)
        printf(" * %f\n", stack_pop(results));
}

stack_t *rpn_eval(char *str) {
    stack_t *stack = stack_new();

    if (operations == NULL)
        rpn_init();

    unsigned short decimal_pos;
    float value;

    char c;
    int i = 0;
    while ((c = str[i++]) != '\0') {

        if (isfloatc(c)) {
            /* prepend 0 if first char is '.' (eg .5 => 0.5, .75 => 0.75) */
            value = (c != '.' ? c - '0' : 0);
            /* keep count of digits after decimal point */
            decimal_pos = (value == 0);

            /* append each consecutive digit to value (base 10)*/
            while (isfloatc(c = str[i])) {
                if (c == '.') {
                    if (decimal_pos > 0) {
                        printf("Unexpected '.'\n");
                        return stack;
                    }
                    decimal_pos++;
                } else if (decimal_pos > 0)
                    /* append digit after '.', inc decimal digit counter */
                    value = value + ((c - '0') / pow(10, decimal_pos++));
                else {
                    /* shift left and append digit */
                    value = value * 10 + c - '0';
                }
                i++;
            }

            stack_put(stack, value);
        } else if (!isblank(c)) {
            rpn_performOperation(stack, c);
        }
    }

    return stack;
}
