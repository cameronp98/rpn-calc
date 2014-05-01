#include "opmap.h"

#include <stdio.h>
#include <stdlib.h>

void error(char *msg) {
    printf("Error: \"%s\"", msg);
    exit(EXIT_FAILURE);
}

opmap_t* opmap_new(size_t cap) {
    opmap_t *temp = malloc(sizeof *temp);
    if (temp == NULL)
        error("memory error");
    temp->maps = calloc(cap, sizeof(cbmap_t));
    temp->cap = cap;
    temp->size = 0;
    return temp;
}

cbmap_t* cbmap_new(char sym, cbptr *func) {
    cbmap_t *temp = malloc(sizeof *temp);
    if (temp == NULL)
        error("memory error");
    temp->sym = sym;
    temp->func = func;
    return temp;
}

int opmap_getMapIndex(opmap_t *map, char sym) {
    for (int i = 0; i < map->size; i++) {
        if (map->maps[i]->sym == sym)
            return i;
    }
    return -1;
}

cbmap_t* opmap_getMapByIndex(opmap_t *map, int idx) {
    if (idx > map->size || idx < 0)
        return NULL;
    return map->maps[idx];
}

cbmap_t* opmap_getMapBySymbol(opmap_t *map, char sym) {
    int idx = opmap_getMapIndex(map, sym);
    if (idx == -1)
        return NULL;
    return map->maps[idx];
}

cbptr* opmap_getFuncByIndex(opmap_t *map, int idx) {
    cbmap_t *cb = opmap_getMapByIndex(map, idx);
    if (cb == NULL)
        return NULL;
    return cb->func;
}

cbptr* opmap_getFuncBySymbol(opmap_t *map, char sym) {
    int idx = opmap_getMapIndex(map, sym);
    return opmap_getMapByIndex(map, idx)->func;
}

char opmap_getSymByIndex(opmap_t *map, int idx) {
    cbmap_t *cb = opmap_getMapByIndex(map, idx);
    if (cb == NULL)
        return -1;
    return cb->sym;
}

void opmap_delete(opmap_t *map) {
    if (map->cap == 0)
        return;

    for (int i = 0; i < map->cap; i++)
        free(map->maps[i]);
    free(map);
}

void opmap_addMap(opmap_t *map, char sym, cbptr *func) {
    if (map->size == map->cap) {
        map->maps = realloc(map->maps, 1 + sizeof(map->maps));
        if (map->maps == NULL)
            error("memory error");
    }

    if (opmap_getMapIndex(map, sym) != -1)
        error("duplicate symbol");

    map->maps[map->size] = cbmap_new(sym, func);
    map->size++;
}

