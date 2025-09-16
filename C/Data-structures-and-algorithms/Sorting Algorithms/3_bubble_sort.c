#include "data_loader.h"

/*
    Bubble sort works by comparing two values `a` and `b` at a time and then 
    swapping their places if `a` is larger than `b`. This algorithm can start at
    either end of the array. And so, its tendency is to move the highest or smallest
    value elements towards the end of the array. In other words, elements "bubble"
    towards the top.
    
    Like most algorithms of its calibre, this has a time complexity of O(n^2). 
    There are two loops here again: the first is simply to restart the process
    at the head, the second is for swapping continuously until the end of the array.

*/

int main() {
    int* integer_array = populate_random_integer_array();

    int sorted_count = DATA_SIZE - 1;
    int temp = 0, is_sorted = 1;
    int integer_array_index = 0;

    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting bubble sort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    while(is_sorted == 1) {
        is_sorted = 0;
        
        /*
            Always start from the head of the array, at index 0. 
        */
        for(integer_array_index = 0; integer_array_index < sorted_count - 1; integer_array_index++) {
            /*
                We check if the value in index `i` is larger than `i + 1`
            */
            if(integer_array[integer_array_index] >= integer_array[integer_array_index + 1]) {
                /*
                    If it is, we swap the value in `i` with `i + 1`. 
                */
                temp = integer_array[integer_array_index];
                integer_array[integer_array_index] = integer_array[integer_array_index + 1];
                integer_array[integer_array_index + 1] = temp;
                is_sorted = 1;
            }

            /*
                We do this until we have reached the end of the array, or the
                head of the sorted part. 
            */
        }

        /*
            We decrease sorted_count as this implementation of the algorithm sorts
            from the end of the array.
        */
        sorted_count--;
    }
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(integer_array);

    free(integer_array);

    return 0;
}