#include "singly.h"

void s_add_to_list(singly* head_node, int value) {
    int running = 1;

    singly* ptr = head_node;

    while(running) {
        if(ptr->value == SENTINEL_VALUE) {
            ptr->value = value;
            ptr->next_node = malloc(sizeof(singly));
            *ptr->next_node = s_NULL_NODE;

            running = 0;
        } else {
            ptr = ptr->next_node;
        }
    }
}

void s_view_list(singly* head_node) {
    int running = 1, list_count = 0;

    singly* ptr = head_node;

    printf("\n\n    Index\n");

    while(running) {
        if(ptr->value != SENTINEL_VALUE) {
            printf("    %d        Value:   %d   \n", list_count, ptr->value);
            printf("             Pointer: %p   \n", ptr);
            printf("             Next:    %p   \n\n", ptr->next_node);
            ptr = ptr->next_node;
            list_count++;
        } else {
            running = 0;
        }
    }
}

void s_delete_node(singly* head_node, int value) {
    int running = 1;

    singly* ptr_1 = head_node;
    singly* ptr_2 = malloc(sizeof(singly));

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

void singly_loop() {
    int running = 1, commandInput = -1;

    int value = 0;

    singly* head_node = malloc(sizeof(singly));
    *head_node = s_NULL_NODE;

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

                    s_add_to_list(head_node, value);
                    break;
                case 2:
                    printf("\n    LINKED LIST\n\n");
                    s_view_list(head_node);
                    break;
                case 3:
                    printf("Insert positive integer value: ");
                    scanf("%d", &value);

                    s_delete_node(head_node, value);
                    break;

                case 4:
                    running = 0;
                    break;

                default:
                    printf("Invalid input.\n");
        }
    }
}


