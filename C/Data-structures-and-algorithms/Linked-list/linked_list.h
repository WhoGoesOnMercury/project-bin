#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define SENTINEL_VALUE -1;

typedef struct node {
    int value;
    struct node* pointer;
} node;

static node NULL_NODE = {SENTINEL_VALUE, NULL};

