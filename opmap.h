#ifndef OPMAP_H
#define OPMAP_H

#include <stdlib.h>

typedef float (cbptr)(float left, float right);

typedef struct callback {
    char sym;
    struct callback *prev;
    cbptr *func;
} cbmap_t;

typedef struct {
    size_t cap;
    size_t size;
    cbmap_t **maps;
} opmap_t;

// ----------------------------------------------------------------------------

static void error(char *msg);

opmap_t* opmap_new(size_t capacity);
cbmap_t* cbmap_new(char symbol, cbptr *func_ptr);

int      opmap_getMapIndex(opmap_t *map, char symbol);

cbmap_t* opmap_getMapByIndex(opmap_t *map, int index);
cbmap_t* opmap_getMapBySymbol(opmap_t *map, char symbol);

cbptr*   opmap_getFuncByIndex(opmap_t *map, int index);
cbptr*   opmap_getFuncBySymbol(opmap_t *map, char symbol);

char     opmap_getSymByIndex(opmap_t *map, int index);

void     opmap_delete(opmap_t *map);
void     opmap_addMap(opmap_t *map, char symbol, cbptr *func_ptr);


#endif
