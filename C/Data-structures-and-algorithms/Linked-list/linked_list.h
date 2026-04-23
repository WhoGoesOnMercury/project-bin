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
    struct node* prev_node;
    int value;
    struct node* next_node;
} node;

static struct node NULL_NODE = {NULL, SENTINEL_VALUE, NULL};

typedef struct linked_list {
    struct node* head_node;
    struct node* tail_node;
    int count;
} linked_list;

static struct linked_list EMPTY_LIST = {NULL, NULL, 0};

void add_to_list(linked_list* linked_list, int value, int mode);
void view_list(linked_list* linked_list, int mode);
void delete_node(node* head_node, int value);