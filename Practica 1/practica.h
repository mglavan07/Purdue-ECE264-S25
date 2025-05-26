#ifndef __PRACTICA_1_B__
#define __PRACTICA_1_B__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Struct representing a single entry in the index.
 *   key represents a string between 0 and 99 characters, null terminated.
 *   value represents a 4 byte integer value.
 */
typedef struct {
    char key[100];
    int value;
} Entry;

/*
 * Struct representing the full index.
 *   entries is an array of entry structs containing each key value pair.
 *   size is the size of the entry array.
 * If size is 0, entries is expected to be NULL.
 */
typedef struct {
    Entry* entries;
    int size;
} Index;

Index read_index(const char* filename);

#endif
