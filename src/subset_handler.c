#include <stdio.h>
#include <stdlib.h>
#include "subset_handler.h"

void find_smallest_subset(data_entry_t* data_entry) {
    if((data_entry->elements_sequence_size) > (data_entry->input_array_size) || (data_entry->elements_sequence_size) == 0)
        printf("Invalid");

    int start = 0, end = 0, smallest_subset_start_index = 0, smallest_subset_end_index = 0, min_window_length = 0;
    int first_subset = 1;

    while(end < (data_entry->input_array_size)) {
        int current_index_in_sequence = 0;
        while(end < (data_entry->input_array_size) && current_index_in_sequence < (data_entry->elements_sequence_size)) {
            if(data_entry->input_array[end] == data_entry->elements_sequence[current_index_in_sequence])
                current_index_in_sequence++;
            end++;
        }

        if(end == (data_entry->input_array_size) && current_index_in_sequence < (data_entry->elements_sequence_size))
            break;

        current_index_in_sequence = (data_entry->elements_sequence_size) - 1;
        start = end - 1;

        if(start != (data_entry->input_array_size)) {
            while(start >= 0 && current_index_in_sequence >= 0) {
                if(data_entry->input_array[start] == data_entry->elements_sequence[current_index_in_sequence])
                    current_index_in_sequence--;
                start--;
            }

            start++;

            if(first_subset || (end - start) < min_window_length) {
                min_window_length = end - start;
                smallest_subset_start_index = start;
                smallest_subset_end_index = end - 1;
                first_subset = 0;
            }
        }
        end = start + 1;
    }
    print_data(data_entry);
    printf("Start index: %d\n", smallest_subset_start_index);
    printf("End Index: %d\n\n", smallest_subset_end_index);
}

void print_data(data_entry_t* data_entry) {
    int     index = 0;      /* Loop iterator */
    printf("Input array size: %d\n", data_entry->input_array_size);
    printf("Elements sequence size: %d\n", data_entry->elements_sequence_size);

    for(index = 0; index < (data_entry->input_array_size); index++) {
        printf("%d ", data_entry->input_array[index]);
    }
    printf("\n");

    for(index = 0; index < (data_entry->elements_sequence_size); index++) {
        printf("%d ", data_entry->elements_sequence[index]);
    }
    printf("\n");
}
