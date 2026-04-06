#include "linked_list.h"

void add_to_list(node* head_node, int value) {
    int running = 1;

    node* ptr = head_node;

    while(running) {
        if(ptr->value == SENTINEL_VALUE) {
            ptr->value = value;
            ptr->next_node = malloc(sizeof(node));
            *ptr->next_node = NULL_NODE;

            running = 0;
        } else {
            ptr = ptr->next_node;
        }
    }
}

void view_list(node* head_node) {
    int running = 1, list_count = 0;

    node* ptr = head_node;

    printf("\n\n    Index\n");

    while(running) {
        if(ptr->value != SENTINEL_VALUE) {
            printf("    %d        Value:   %d   \n", list_count, ptr->value);
            printf("             Pointer: %p   \n\n", ptr->next_node);
            ptr = ptr->next_node;
            list_count++;
        } else {
            running = 0;
        }
    }
}

void delete_node(node* head_node, int value) {
    int running = 1;

    node* ptr_1 = head_node;
    node* ptr_2 = malloc(sizeof(node));

    while(running) {
        if(ptr_1->value == value) {
            ptr_2->next_node = ptr_1->next_node;
            free(ptr_1);
            running = 0;
        } else if(ptr_1->next_node == NULL) {
            printf("\nValue \"%d\" does not exist in the linked list.", value);
            running = 0;
        } else {
            ptr_2 = ptr_1;
            ptr_1 = ptr_1->next_node;
        }
    }
}




