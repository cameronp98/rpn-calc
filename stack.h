#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct stack_node {
    struct stack_node *prev;
    float value;
} node_t;

typedef struct {
    size_t size;
    node_t *tail;
} stack_t;

static void error(char *message);

node_t  *node_new(float value);

stack_t *stack_new();
void     stack_del(stack_t *stack);
void     stack_put(stack_t *stack, float value);
float    stack_pop(stack_t *stack);

#endif
