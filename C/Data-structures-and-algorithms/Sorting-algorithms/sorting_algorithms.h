#include "data_loader.h"

void printHeader() {
    system("cls");
    const char *header =
    "=====================================================\n"
    "  ####                     #                         \n"
    " #                         #     #                   \n"
    " #        ####    ####   #####        ####    ####   \n"
    "  ###    #    #  #    #    #     #   #    #  #    #  \n"
    "     #   #    #  #         #     #   #    #  #    #  \n"
    "     #   #    #  #         #     #   #    #  #    #  \n"
    " ####     ####   #         #     #   #    #   ####   \n"
    "                                                  #  \n"
    "                                                  #  \n"
    "                                              ####   \n"
    "                                 ####                \n"
    "             #                  #                    \n"
    "                  ####          #                    \n"
    "             #   #    #         #                    \n"
    "             #   #    #         #                    \n"
    "             #   #    #         #                    \n"
    "             #   #    #          ####                \n"
    "=====================================================\n";

    printf("%s", header);
    printf("           This is made by WhoGoesOnMercury\n\n\n");
}

void selection_sort(int* integer_array) {
    int* inside_array = malloc(DATA_SIZE * sizeof(int));
    memcpy(inside_array, integer_array, DATA_SIZE * sizeof(int));

    int swap_index = 0, temp = 0;

    clock_t elapsed_time;

    elapsed_time = clock();

    for(int i = 0; i < DATA_SIZE - 1; i++) {
        swap_index = i;
        for(int j = i + 1; j < DATA_SIZE; j++) {
            if(inside_array[j] <= inside_array[swap_index]) {
                swap_index = j;
            }
        }
        temp = inside_array[i];
        inside_array[i] = inside_array[swap_index];
        inside_array[swap_index] = temp;
    }

    elapsed_time = clock() - elapsed_time;

    printf("Selection Sort time: %f\n", (double)elapsed_time / CLOCKS_PER_SEC);

    free(inside_array);
}

void insertion_sort(int* integer_array) {
    int* inside_array = malloc(DATA_SIZE * sizeof(int));
    memcpy(inside_array, integer_array, DATA_SIZE * sizeof(int));

    int swap_index = -1, unsorted_array_index = -1;
    int temp = 0, inner_loop = 0;
    int integer_array_index = 0;

    clock_t elapsed_time;

    elapsed_time = clock();
   
    for(integer_array_index = 0; integer_array_index < DATA_SIZE - 1; integer_array_index++) {
        swap_index = integer_array_index;
        unsorted_array_index = integer_array_index + 1;
        inner_loop = 1;
        while(swap_index != -1 && inner_loop == 1) {
            if(inside_array[unsorted_array_index] >= inside_array[swap_index]) {
                inner_loop = 0;
            } else {
                temp = inside_array[swap_index];
                inside_array[swap_index] = inside_array[unsorted_array_index];
                inside_array[unsorted_array_index] = temp;
                unsorted_array_index--;
                swap_index--;
            }
        }
    }
    elapsed_time = clock() - elapsed_time;

    printf("Insertion sort time: %f\n", (double)elapsed_time / CLOCKS_PER_SEC);

    free(inside_array);
}

void bubble_sort(int* integer_array) {
    int* inside_array = malloc(DATA_SIZE * sizeof(int));
    memcpy(inside_array, integer_array, DATA_SIZE * sizeof(int));

    int sorted_count = DATA_SIZE - 1;
    int temp = 0, is_sorted = 1;
    int integer_array_index = 0;

    clock_t elapsed_time;

    elapsed_time = clock();

    while(is_sorted == 1) {
        is_sorted = 0;
        for(integer_array_index = 0; integer_array_index < sorted_count - 1; integer_array_index++) {
            if(inside_array[integer_array_index] >= inside_array[integer_array_index + 1]) {
                temp = inside_array[integer_array_index];
                inside_array[integer_array_index] = inside_array[integer_array_index + 1];
                inside_array[integer_array_index + 1] = temp;
                is_sorted = 1;
            }
        }
        sorted_count--;
    }
    elapsed_time = clock() - elapsed_time;

    printf("Bubble sort time: %f\n", (double)elapsed_time / CLOCKS_PER_SEC);

    free(inside_array);
}

void counting_sort(int* integer_array) {
    int* inside_array = malloc(DATA_SIZE * sizeof(int));
    memcpy(inside_array, integer_array, DATA_SIZE * sizeof(int));

    int *counting_array = calloc(MAX_INT_VALUE + 1, sizeof(int));
    int integer_array_index = 0, value = 0;

    clock_t elapsed_time;

    elapsed_time = clock();

    for(integer_array_index = 0; integer_array_index < DATA_SIZE; integer_array_index++) {
        value = inside_array[integer_array_index];
        counting_array[value] = counting_array[value] + 1;
    }
    int count_index = 0;
    integer_array_index = 0;
    while(integer_array_index < DATA_SIZE) {
        if(counting_array[count_index] == 0 && count_index < MAX_INT_VALUE) {
            count_index++;
            continue;
        }
        inside_array[integer_array_index] = count_index;
        counting_array[count_index]--;
        integer_array_index++;
    }
    elapsed_time = clock() - elapsed_time;

    printf("Counting sort time: %f\n", (double)elapsed_time / CLOCKS_PER_SEC);

    free(counting_array);
    free(inside_array);
}

int partition(int* integer_array, int low, int high) {
    int pivot = integer_array[high];
    int index = low - 1;
    int temp = 0;

    for (int integer_array_index = low; integer_array_index <= high - 1; integer_array_index++) {
        if(integer_array[integer_array_index] < pivot) {
            index++;
            temp = integer_array[index];
            integer_array[index] = integer_array[integer_array_index];
            integer_array[integer_array_index] = temp;
        }
    }

    temp = integer_array[index + 1];
    integer_array[index + 1] = integer_array[high];
    integer_array[high] = temp;

    return (index + 1);
}

void quick_sort(int* integer_array, int low, int high) {
    if (low < high) {
        int pivot_index = partition(integer_array, low, high);

        quick_sort(integer_array, low, pivot_index - 1);
        quick_sort(integer_array, pivot_index + 1, high);
    }
}

typedef struct {
    int* data;
    int count;
} bucket;

void radix_sort(int* integer_array) {
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

    while (max != 0) {
        digit_count++;
        max /= 10;        
    }

    clock_t elapsed_time;

    elapsed_time = clock();

    for(int i = 1; i < digit_count; i++) {
        /*
        `size` will serve as the index
        */
        size = DATA_SIZE - 1;

        digit *= 10;
        for(int integer_array_index = 0; integer_array_index < DATA_SIZE; integer_array_index++) {
            value = integer_array[integer_array_index] % digit;

            value /= (digit / 10);
            
            buckets[value].data[buckets[value].count] = integer_array[integer_array_index];
            buckets[value].count++;
            
        }

        for(int j = 9; j >= 0; j--) {
            for(int bucket_emptier = buckets[j].count - 1; bucket_emptier >= 0; bucket_emptier--) {
                integer_array[size] = buckets[j].data[bucket_emptier];
                size--;
            }
            buckets[j].count = 0;
        }
    }

    elapsed_time = clock() - elapsed_time;

    printf("Radix sort time: %f\n", (double)elapsed_time / CLOCKS_PER_SEC);

    for(int i = 0; i < 10; i++) {
        free(buckets[i].data);
    }
}

int* merge(int* left, int* right, int left_size, int right_size) {
    int* resulting_array = calloc(left_size + right_size, sizeof(int));
    int i = 0, j = 0, k = 0;

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


int* merge_sort(int* integer_array, int size) {
    if(size <= 1) {
        return integer_array;
    }

    int left_size = 0, right_size = 0;

    if(size % 2 == 1) {
        left_size = (size / 2) + 1;
        right_size = size / 2;
    } else {
        left_size = right_size = size / 2;
    }

    int* left = calloc(left_size, sizeof(int));
    int* right = calloc(right_size, sizeof(int));

    memcpy(left, integer_array, left_size * sizeof(int));
    memcpy(right, integer_array + left_size, right_size * sizeof(int));

    left = merge_sort(left, left_size);
    right = merge_sort(right, right_size);

    return merge(left, right, left_size, right_size);
}