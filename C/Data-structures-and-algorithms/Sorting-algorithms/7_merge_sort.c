#include "data_loader.h"

/*
    Merge sort is another divide-and-conquer algorithm. Here, we break down the
    initial array into smaller sub-arrays and then recreating and sorting along
    the way.

    Unlike quick sort, merge sort does not need a pivot element. Once the array
    has been broken down into singular arrays, the values are placed on an array
    that has a size equal to the two arrays it is built from. While values are
    being placed from both arrays, they are compared with each, placing the lower
    values first each time. This process repeats until all values are sorted
    and the initial array is rebuilt.

    Merge sort is often implemented with a recursions (as it is seen here) but it
    is possible to create a merge sort algorithm without it. It is just more 
    intuitive to visualize given that its a divide-and-conquer algorithm. The
    main difference (aside from function calls) is by rebuilding the array from
    the start. Start with an array of size 1 and then geometrically increase the 
    size by 2 each time while the sub-array size is lesser than the size of the
    initial array. 
    
    Merge sort's time complexity is O(n log n).
*/

int* merge(int* left, int* right, int left_size, int right_size) {
    int* resulting_array = calloc(left_size + right_size, sizeof(int));
    int i = 0, j = 0, k = 0;

    /*
        Compare left and right values and then place them on an array by order
    */
    while (i < left_size && j < right_size) {
        if(left[i] < right[j]) {
            resulting_array[k] = left[i];
            i++;
        } else {
            resulting_array[k] = right[j];
            j++;
        }
        k++;
    }

    /*
        At some point, these two loops will just not go through because left and
        right will be equal. 
    */
    while(i < left_size) {
        resulting_array[k] = left[i];
        k++;
        i++;
    }

    while(j < right_size) {
        resulting_array[k] = right[j];
        k++;
        j++;
    } 

    return resulting_array;
}

/*

*/
int* merge_sort(int* integer_array, int size) {
    /*
        Conditional to return if the size is 1
    */
    if(size <= 1) {
        return integer_array;
    }

    int left_size = 0, right_size = 0;

    /*
        In C, dividing another integer by 2 will round down although not technically.
        If the quotient contains decimals, C truncates those decimals. In other
        words, it cuts them so it looks like the quotient rounds down. To simplify,
        we check if the division will result with 1 as a remainder. 
    */
    if(size % 2 == 1) {
        left_size = (size / 2) + 1;
        right_size = size / 2;
    } else {
        left_size = right_size = size / 2;
    }

    int* left = calloc(left_size, sizeof(int));
    int* right = calloc(right_size, sizeof(int));

    /*
        This is a simple way to copy arrays onto other initialized arrays. If you
        add an integer to a pointer, it moves that pointer by (value of number *
        sizeof(int)). 
    */
    memcpy(left, integer_array, left_size * sizeof(int));
    memcpy(right, integer_array + left_size, right_size * sizeof(int));

    /*
        Recursive call until size is equal to one.
    */
    left = merge_sort(left, left_size);
    right = merge_sort(right, right_size);

    return merge(left, right, left_size, right_size);
}

int main() {
    int* integer_array = populate_random_integer_array();
    int* resulting_array = calloc(DATA_SIZE, sizeof(int));

    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting merge sort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    resulting_array = merge_sort(integer_array, DATA_SIZE);
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(resulting_array);

    free(integer_array);
    free(resulting_array);

    return 0;
}