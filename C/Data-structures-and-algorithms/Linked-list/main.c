#include "linked_list.c"

int main() {
    int running = 1, commandInput = -1, mode = 0;

    int value = 0;

    linked_list* linked_list = malloc(sizeof(linked_list));
    *linked_list = EMPTY_LIST;

    node* head = malloc(sizeof(node));
    node* tail = malloc(sizeof(node));

    *head = NULL_NODE;
    *tail = NULL_NODE;

    linked_list->head_node = head;
    linked_list->tail_node = tail;

    printf("\n=== LINKED LIST TYPE ===\n");
    printf("[1] SINGLY\n");            
    printf("[2] DOUBLY\n"); 
    printf("[3] CIRCULAR\n");            
    printf("[4] EXIT\n");
    printf("Choose Type: ");
    if (scanf("%d", &mode) != 1) {
            printf("Invalid input.\n");
        } 
    
    while(running) {
        printf("\n=== LINKED LIST FUNCTIONS ===\n");
        printf("[1] INSERT NODE\n");            
        printf("[2] DISPLAY LIST\n"); 
        printf("[3] DELETE NODE\n");            
        printf("[4] EXIT\n");
        printf("Choose Function: ");

        if (scanf("%d", &commandInput) != 1) {
                printf("Invalid input.\n"); 
            }

            switch (commandInput) {
                case 1: 
                    printf("Insert positive integer value: ");
                    if (scanf("%d", &value) != 1) {
                        printf("Invalid input.\n");
                    } 

                    add_to_list(linked_list, value, mode);
                    break;
                case 2:
                    printf("\n    LINKED LIST\n");
                    view_list(linked_list);
                    break;
                case 3:
                    printf("Insert positive integer value: ");
                    if (scanf("%d", &value) != 1) {
                        printf("Invalid input.\n");
                    } 

                    delete_node(linked_list->head_node, value);
                    break;

                case 4:
                    running = 0;
                    break;
                default:
                    printf("Invalid input.\n");
        }
    }


    return 0;
}