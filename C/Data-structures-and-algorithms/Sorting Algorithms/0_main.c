#include "sorting_algorithms.h"

/*
    This is the file for the interface. For the meantime, the interface will be 
    handled through the command line. Soon, I plan to transition it to a better GUI 
    but only once I have learned.
*/

int main() {
    int choice = -1, running = 1;
    clock_t elapsed_time;

    printHeader();
    Sleep(1000);

    printf("Generating random integer array...\n");
    printf("Array size: %d\n", DATA_SIZE);
    printf("Maximum integer value: %d\n\n", MAX_INT_VALUE);
    int* integer_array = populate_random_integer_array();
    int* result_array = calloc(DATA_SIZE, sizeof(int));

    while(running) {
        printf("\n=== Sorting Algorithms ===\n");
        printf("[1] SELECTION SORT\n");
        printf("[2] INSERTION SORT\n");
        printf("[3] BUBBLE SORT\n");
        printf("[4] COUNTING SORT\n");
        printf("[5] QUICK SORT\n");
        printf("[6] RADIX SORT\n");
        printf("[7] MERGE SORT\n");
        printf("[8] RUN ALL SORTING ALGORITHMS SEQUENTIALLY\n");
        printf("[9] EXIT PROGRAM\n");
        printf("Choose Command: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                selection_sort(integer_array);
                break;
            case 2: 
                insertion_sort(integer_array);
                break;
            case 3:
                bubble_sort(integer_array); 
                break;
            case 4:
                counting_sort(integer_array); 
                break;
            case 5:
                elapsed_time = clock();
                printf("Quick sort time: ");
                quick_sort(integer_array, 0, DATA_SIZE - 1);
                elapsed_time = clock() - elapsed_time;
                printf("%f\n", (double)elapsed_time / CLOCKS_PER_SEC);
                break;
            case 6:
                radix_sort(integer_array);
                break;
            case 7:
                elapsed_time = clock();
                printf("Merge sort time: ");
                result_array = merge_sort(integer_array, DATA_SIZE);
                elapsed_time = clock() - elapsed_time;
                printf("%f\n", (double)elapsed_time / CLOCKS_PER_SEC);
                break;
            case 8:
                selection_sort(integer_array);
                insertion_sort(integer_array);
                bubble_sort(integer_array);
                counting_sort(integer_array); 
                
                // For quick sort
                elapsed_time = clock();
                printf("Quick sort time: ");
                quick_sort(integer_array, 0, DATA_SIZE - 1);
                elapsed_time = clock() - elapsed_time;
                printf("%f\n", (double)elapsed_time / CLOCKS_PER_SEC);

                radix_sort(integer_array);

                // For merge sort
                elapsed_time = clock();
                printf("Merge sort time: ");
                result_array = merge_sort(integer_array, DATA_SIZE);
                elapsed_time = clock() - elapsed_time;
                printf("%f\n", (double)elapsed_time / CLOCKS_PER_SEC);
                break;
            case 9: 
                printf("Exiting the program...");
                Sleep(10);
                running = 0;
                break;
            default:
                printf("Enter a valid input.");
        }
    }

    free(integer_array);
    free(result_array);
    
    return 0;
}