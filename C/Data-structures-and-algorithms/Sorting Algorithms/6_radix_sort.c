#include "data_loader.h"

/*
    Radix sort works by classifying elements according to their individual digits. 
    Radix always starts with the ones digit until it reaches the maximum value
    element in the array. For this to work, we extract the ones digit and then place 
    it inside a `bucket`—definition below. We do this to the tens, the hundreds, 
    and so on and so forth with placing them back into the initial array as an
    in-between step. 

    Unlike other sorting algorithms, there is a stable and non-stable way for 
    Radix sort. The simple difference between them is that the non-stable radix
    sort starts at the end of the array. How does this lead to non-stability?
    Remember that radix sort works by sorting by individual digits which in turn
    should place lower value elements towards the start of the array. By starting
    from the end, all the work that was placed into sorting them by the previous
    digit will have gone to waste and therefore can yield an unsorted array. 

    The time complexity for radix sort is usually O(n * k), where `n` is the number
    of input data and `k` is the number of digits in the highest element. Assignment
    operators and simple mathematical operations are usually in constant time. This 
    algorithm does not require recursion nor does it need any comparisons between elements. 
*/

/*
    A bucket, as defined here, is simply an array with a counter for how many
    elements are inside. In C, this is the simplest way to keep track of how
    many `active` elements there are in an initialized array. 
*/
typedef struct {
    int* data;
    int count;
} bucket;

int main() {
    int* integer_array = populate_random_integer_array();

    /*
        Define buckets here. Malloc is used to initialize the data[] attribute
        so it is added to the heap. 
    */
    bucket buckets[10];
    for(int i = 0; i < 10; i++) {
        buckets[i].data = malloc(sizeof(int) * DATA_SIZE);
        buckets[i].count = 0;
    }

    int max = MAX_INT_VALUE;
    int size = DATA_SIZE;
    int value = 0;

    int digit_count = 0;
    int digit = 1;

    /*
        Simple way to count the maximum digits that makes the code flexible
    */
    while (max != 0) {
        digit_count++;
        max /= 10;        
    }

    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting radix sort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    for(int i = 1; i < digit_count; i++) {
        /*
        `size` will serve as an index for later use
        */
        size = DATA_SIZE - 1;

        digit *= 10;
        for(int integer_array_index = 0; integer_array_index < DATA_SIZE; integer_array_index++) {
            /*
                We extract the digit by using the modulo operator
            */
            value = integer_array[integer_array_index] % digit;

            /*
                Here, we simply make value a number from 0 to 9. This simplifies
                storing into the different `buckets` by allowing `value` to act
                as the index. 
            */
            value /= (digit / 10);
            
            /*
                Since we have already extracted the digit's value, we simply add
                it to the respective bucket while also increasing the bucket's count.
            */
            buckets[value].data[buckets[value].count] = integer_array[integer_array_index];
            buckets[value].count++;
        }

        /*
            After each element has been placed into a bucket, we simply put them back
            starting from the last bucket (the one that has the digit 9 stored). We
            simply loop through every element inside a bucket and move on to the next
            one until all the buckets are empty.
        */
        for(int j = 9; j >= 0; j--) {
            for(int bucket_emptier = buckets[j].count - 1; bucket_emptier >= 0; bucket_emptier--) {
                integer_array[size] = buckets[j].data[bucket_emptier];
                size--;
            }
            buckets[j].count = 0;
        }
    }
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(integer_array);

    free(integer_array);
    for(int i = 0; i < 10; i++) {
        free(buckets[i].data);
    }

    return 0;
}