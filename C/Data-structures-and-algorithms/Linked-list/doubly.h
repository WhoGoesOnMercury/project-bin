#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define SENTINEL_VALUE -1

typedef struct doubly {
    struct doubly* prev_node;
    int value;
    struct doubly* next_node;
} doubly;

static struct doubly d_NULL_NODE = {NULL, SENTINEL_VALUE, NULL};

