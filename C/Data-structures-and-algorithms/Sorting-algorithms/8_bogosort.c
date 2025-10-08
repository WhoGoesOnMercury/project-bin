#include "data_loader.h"

/*
    Bogosort—contrary to any sort of criteria for algorithms—is an inefficient
    sorting algorithm. It works by shuffling the order of the elements in the
    array and hoping that one of those shuffles results to an already-sorted
    array. Bogosort is also known as permutation sort.

    Unlike any other algorithm, bogosort does not have an upper-bound time 
    complexity. Due to the pseudo-random nature of generating numbers through 
    the srand() and rand() functions, bogosort may not even fully terminate even
    if it has reached the average time complexity which is generally O(n!). Although
    even if the generated numbers were truly random, bogosort would still prove 
    unreliable because of its reliance on chance. A basic probabilities explanation 
    would be (for five numbers):
        5 x 4 x 3 x 2 x 1 || 5!               General permutation 
*/


int is_sorted(int* integer_array, int arr_size) {
    int i = 0;

    /*
        This loop checks if the array is sorted, simply returning 0 or false
        and 1 or true.
    */
    while(i < arr_size - 1) {
        if(integer_array[i] > integer_array[i + 1]) {
            return 0;
        }
        i++;
    }

    return 1;
}

void shuffle (int* integer_array, int arr_size) {
    int temp = 0, random = 0;
    for(int i = 0; i < arr_size; i++) {
        /*
            Swap elements pseudo-randomly
        */
        random = rand() % arr_size;
        temp = integer_array[i];
        integer_array[i] = integer_array[random];
        integer_array[random] = temp;
        temp = 0;
    }
}

int main() {
    int* integer_array = populate_random_integer_array();


    clock_t elapsed_time;

    elapsed_time = clock();
    printf("Starting bogosort...\n\n");

    //       |--- START OF THE ALGORITHM ---|
    srand (time(NULL));
    while(!is_sorted(integer_array, DATA_SIZE)) {
        shuffle(integer_array, DATA_SIZE);
    }
    //       |--- END OF THE ALGORITHM ---|
    elapsed_time = clock() - elapsed_time;

    printf("Sorting time: %f", (double)elapsed_time / CLOCKS_PER_SEC);

    print_sorted_values(integer_array);

    free(integer_array);

    return 0;
}