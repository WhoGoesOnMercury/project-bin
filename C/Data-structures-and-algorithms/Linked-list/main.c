#include "singly.c"
#include "doubly.c"

int main() {
    
    int input = 0;

    printf("Input: ");
    scanf("%d", &input);

    switch(input) {
        case 1:
            singly_loop();
            break;
        case 2:
            doubly_loop();
            break;
        case 3:
            //circular_loop();
            break;
        default:
            break;
    }

    return 0;
}