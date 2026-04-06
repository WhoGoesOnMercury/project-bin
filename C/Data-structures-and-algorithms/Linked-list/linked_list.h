#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define SENTINEL_VALUE -1

typedef struct node {
    int value;
    struct node* next_node;
} node;

static struct node NULL_NODE = {SENTINEL_VALUE, NULL};

