#include "stack.h"

#include <stdio.h>

void error(char *msg) {
    printf("stack error: \"%s\"", msg);
    exit(EXIT_FAILURE);
}

node_t *node_new(float value) {
    node_t *temp = malloc(sizeof(*temp));
    if (temp == NULL)
        error("memory error\n");
    temp->value = value;
    temp->prev = NULL;
    return temp;
}

stack_t *stack_new() {
    stack_t *temp = malloc(sizeof(*temp));
    if (temp == NULL)
        error("memory error\n");
    temp->size = 0;
    temp->tail = NULL;
    return temp;
}

void stack_put(stack_t *st, float value) {
    node_t *new = node_new(value);
    if (st->tail == NULL)
        st->tail = new;
    else {
        node_t *oldTail = st->tail;
        (st->tail = new)->prev = oldTail;
    }
    st->size++;
}

float stack_pop(stack_t *st) {
    if (st->size == 0)
        error("stack underflow");

    float value = st->tail->value;
    node_t *oldTail = st->tail;

    st->tail = oldTail->prev;
    free(oldTail);

    st->size--;

    return value;
}

void stack_del(stack_t *st) {
    if (st->size > 0) {
        node_t *node = st->tail, *prev;
        int i;
        for (i = 0; i < st->size; i++) {
            prev = node->prev;
            free(node);
            node = prev;
        }
    }
    free(st);
}
