#include "data_loader.h"

/*
    Quick sort is the first recursive sorting that we will be dealing with. The 
    concept of quick sort revolves around the idea of a divide-and-conquer—simply
    it is when we "divide" a problem into smaller and more "conquerable" problems.
    
    Our problem here is to sort. First, we choose a value from the array and we 
    will call this our pivot (there are various ways to go about this but random 
    will always yield the most consistent results). Every value in the left of the
    pivot that is larger will be swapped to the right, and every value in the right
    that is larger will be swapped to the left. We will now have two arrays: one
    that has values lower than our pivot and another with higher values. In the
    lower-value array, we choose another pivot at random and then do the same
    as our initial array. We also do this for the higher-value array. We continue
    this process until there are no more sub-arrays formed. 

    Time complexity...
*/

int partition(int* integer_array, int low, int high) {
    /*
        Here, the pivot that is utilized is the last value of the sub-array
    */
    int pivot = integer_array[high];
    int index = low - 1;
    int temp = 0;

    /*
        Loop through all the elements in the sub-array
    */
    for (int integer_array_index = low; integer_array_index <= high - 1; integer_array_index++) {
        /*
            Check if the value is smaller than our pivot so the swapping can be
            initiated
        */
        if(integer_array[integer_array_index] < pivot) {
            /*
                This index increment refers to the values smaller than `pivot`
            */
            index++;

            /*
                Swap current element to left side of the pivot
            */
            temp = integer_array[index];
            integer_array[index] = integer_array[integer_array_index];
            integer_array[integer_array_index] = temp;
        }
    }

    /*
        The pivot is placed between the lower and higher values. Remember that
        the lower values are all stored at our initial `index` to `index` at the
        end of the loop. 
    */
    temp = integer_array[index + 1];
    integer_array[index + 1] = integer_array[high];
    integer_array[high] = temp;

    /*
        Simply return the index of the pivot
    */
    return (index + 1);
}


void quick_sort(int* integer_array, int low, int high) {
    /*
        We use this checker to see if the values are already sorted. At some
        point, `low` will be equal to `high` and that is the indicator that
        to resolve this function call. 
    */
    if (low < high) {
        int pivot_index = partition(integer_array, low, high);

        quick_sort(integer_array, low, pivot_index - 1);
        quick_sort(integer_array, pivot_index + 1, high);
    }
}


int main() {
    int* integer_array = populate_random_integer_array();

    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting quick sort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    quick_sort(integer_array, 0, DATA_SIZE - 1);
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(integer_array);

    free(integer_array);

    return 0;
}
