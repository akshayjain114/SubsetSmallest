#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subset_handler.h"

int parse_and_store_in_array(int* array, int length, char* line) {
    char*   separator = ",";
    char*   value_ptr = NULL;
    int     value = 0;
    int     index = 0;

    value_ptr = strtok(line, separator);
    while(value_ptr != NULL) {
            sscanf(value_ptr, "%d", &value);
            array[index] = value;
            index++;
            value_ptr = strtok(NULL, separator);
    }

    if(index != length) {
            printf("Insufficient number of entries for the input array.\n");
            return 0;
    }
}

int read_data_from_file(char* file_name, data_entry_t* data_entry) {
    FILE*       file_ptr;
    char*       line = NULL;
    ssize_t     num_of_chars_read = 0;
    size_t      length = 0;
    int         line_num = 1;
    int         index = 0;                  /* Loop iterator */

    /* Open file for reading data from it */
    file_ptr = fopen(file_name, "r");
    if(file_ptr == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    while((num_of_chars_read = getline(&line, &length, file_ptr)) != -1) {
        if(num_of_chars_read != 2) {

            switch (line_num) {
                case 1:
                    data_entry->input_array_size = atoi(line);
                    break;
                case 2:
                    data_entry->elements_sequence_size = atoi(line);
                    break;
                case 3:
                    data_entry->input_array = malloc(sizeof(int) * (data_entry->input_array_size));

                    if(!parse_and_store_in_array(data_entry->input_array, data_entry->input_array_size, line)) {
                        printf("Input array parsing failed.\n");
                        return 0;
                    }
                    break;
                case 4:
                    data_entry->elements_sequence = malloc(sizeof(int) * (data_entry->elements_sequence_size));

                    if(!parse_and_store_in_array(data_entry->elements_sequence, data_entry->elements_sequence_size, line)) {
                        printf("Elements sequence array parsing failed.\n");
                        return 0;
                    }
                    break;
            }

            if(line_num == 4) {
                find_smallest_subset(data_entry);
                free(data_entry->input_array);
                free(data_entry->elements_sequence);
                line_num = 0;
            }

            line_num++;
        }
    }
    
    fclose(file_ptr);
    return 1;
}
