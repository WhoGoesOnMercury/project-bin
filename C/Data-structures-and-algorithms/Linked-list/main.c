#include "linked_list.c"

int main() {
    int running = 1, commandInput = -1;

    int value = 0;

    node* head_node = malloc(sizeof(node));
    *head_node = NULL_NODE;

    while(running) {
        printf("\n=== LINKED LIST MENU ===\n");
        printf("[1] INSERT NODE\n");            
        printf("[2] CHECK IF VALUE EXISTS\n"); 
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

                    add_to_list(head_node, value);

                    break;
                    
                case 2:
                    view_list(head_node);
                    break;

                case 3:
                   
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