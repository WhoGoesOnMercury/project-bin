#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#define SENTINEL_VALUE -1

typedef struct singly {
    int value;
    struct singly* next_node;
} singly;

static struct singly s_NULL_NODE = {SENTINEL_VALUE, NULL};

