#include "doubly.h"


void d_add_to_list(doubly* head_node, int value) {
    int running = 1;

    doubly* ptr_1 = head_node;
    doubly* ptr_2 = malloc(sizeof(doubly));

    while(running) {
        if(ptr_1->value == SENTINEL_VALUE) {
            ptr_1->value = value;
            ptr_1->prev_node = ptr_2;
            ptr_1->next_node = malloc(sizeof(doubly));
            *ptr_1->next_node = d_NULL_NODE;

            running = 0;
        } else {
            ptr_2 = ptr_1;
            ptr_1 = ptr_1->next_node;
        }
    }
}

void d_view_list(doubly* head_node) {
    int running = 1, list_count = 0;

    doubly* ptr = head_node;

    printf("\n\n    Index\n");

    while(running) {
        if(ptr->value != SENTINEL_VALUE) {
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

void d_delete_node(doubly* head_node, int value) {
    int running = 1;

    doubly* ptr_1 = head_node;
    doubly* ptr_2 = malloc(sizeof(doubly));

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

void doubly_loop() {
    int running = 1, commandInput = -1;

    int value = 0;

    doubly* head_node = malloc(sizeof(doubly));
    *head_node = d_NULL_NODE;

    while(running) {
        printf("\n=== LINKED LIST MENU ===\n");
        printf("[1] INSERT NODE\n");            
        printf("[2] DISPLAY LIST\n"); 
        printf("[3] DELETE NODE\n");            
        printf("[4] EXIT\n");
        printf("Choose Command: ");

        if (scanf("%d", &commandInput) != 1) {
                printf("Invalid input.\n");
                while (getchar() != '\n'); 
                continue;
            }
            while (getchar() != '\n'); 

            switch (commandInput) {
                case 1: 
                    printf("Insert positive integer value: ");
                    scanf("%d", &value);

                    d_add_to_list(head_node, value);
                    break;
                case 2:
                    printf("\n    LINKED LIST\n\n");
                    d_view_list(head_node);
                    break;
                case 3:
                    printf("Insert positive integer value: ");
                    scanf("%d", &value);

                    d_delete_node(head_node, value);
                    break;

                case 4:
                    running = 0;
                    break;

                default:
                    printf("Invalid input.\n");
        }
    }
}



