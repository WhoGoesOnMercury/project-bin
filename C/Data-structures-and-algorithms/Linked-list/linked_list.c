#include "linked_list.h"

void add_to_list(linked_list* linked_list, int value, int mode) {
    int running = 1;

    node* ptr_1 = linked_list->head_node;
    node* ptr_2 = malloc(sizeof(node));
    node* tail = linked_list->tail_node;

    while(running) {
        if(ptr_1->value == SENTINEL_VALUE || ptr_1 != tail) {
            ptr_1->value = value;
            ptr_1->next_node = malloc(sizeof(node));
            *ptr_1->next_node = NULL_NODE;

            switch(mode) {
                case 2:
                    ptr_1->prev_node = ptr_2;
                    break;
                case 3:
                    ptr_1->prev_node = ptr_2;
                    ptr_1->next_node = linked_list->head_node;
                    linked_list->tail_node = ptr_1;
                    break;
            }

            running = 0;
        } else {
            ptr_2 = ptr_1;
            ptr_1 = ptr_1->next_node;
        }
    }
}

void view_list(linked_list* linked_list) {
    int running = 1, list_count = 0;

    node* ptr = linked_list->head_node;
    node* tail = linked_list->tail_node;

    printf("    Index\n");
 
    while(running) {
        if(ptr->value != SENTINEL_VALUE || ptr != tail) {
            printf("    %d        Previous: %p  \n", list_count, ptr->prev_node);
            printf("             Value:    %d   \n", ptr->value);
            printf("             Pointer:  %p   \n", ptr);
            printf("             Next:     %p   \n\n", ptr->next_node);
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

    free(ptr_2);
}
