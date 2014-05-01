#include "opmap.h"

#include <stdio.h>

float _add(float a, float b) { return a + b; }
float _sub(float a, float b) { return a - b; }

int main() {
    opmap_t *ops = opmap_new(6);
    opmap_addMap(ops, '+', _add);
    opmap_addMap(ops, '-', _sub);

    float a = 10, b = 5;
    cbmap_t *cb;

    for (int i = 0; i < ops->size; i++) {
        cb = opmap_getMapByIndex(ops, i);
        printf("%f %c %f = %f\n", a, cb->sym, b, cb->func(a, b));
    }

    printf("%f\n", opmap_getFuncByIndex(ops, 0)(3, 4));

    return 0;
}
