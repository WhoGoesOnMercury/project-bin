#include "data_loader.h"

/*
    Counting sort works by individually counting the occurrences of an element
    and then incrementing a counter corresponding to that element. Using integers,
    this can be simply done through incrementing at the index equal to the element.
    If an element has a value of `30` then the counter at index 30 will be incremented.
    This is the core of counting sort and can be implemented in various ways.

    This algorithm has a time complexity of O(n + k), where `n` is the amount of data
    (in our case DATA_SIZE) and `k` is the maximum value in the array. This sorting
    algorithm is quite fast compared to the previous ones as it does not require any
    comparisons nor does it have to iterate through an array plentiful times.
*/

int main() {
    int* integer_array = populate_random_integer_array();

    int *counting_array = calloc(MAX_INT_VALUE + 1, sizeof(int));
    int integer_array_index = 0, value = 0;

    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting counting sort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    /*
        We first count each instance of a value by iterating through the whole
        array and then incrementing at the index equal to the value
    */
    for(integer_array_index = 0; integer_array_index < DATA_SIZE; integer_array_index++) {
        value = integer_array[integer_array_index];
        counting_array[value] = counting_array[value] + 1;
    }

    int count_index = 0;

    integer_array_index = 0;
    while(integer_array_index < DATA_SIZE) {
        /*
            We skip the indices or values that are zero
        */
        if(counting_array[count_index] == 0 && count_index < MAX_INT_VALUE) {
            count_index++;
            continue;
        }
        
        /*
            We "sort" by replacing the value at the index in the integer array by
            the count index. We then decrement the count to mark that we have placed
            one instance of that value.
        */
        integer_array[integer_array_index] = count_index;
        counting_array[count_index]--;
        integer_array_index++;
    }
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(integer_array);

    free(counting_array);
    free(integer_array);

    return 0;
}

/*
    Note that while this sorting algorithm is quite efficient, this implementation
    is only the core. This algorithm will not work if there are negative values;
    it will throw an array index out-of-bounds. 
*/