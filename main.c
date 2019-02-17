#include <stdio.h>
#include <stdlib.h>
#include "src/subset_handler.h"

static int validate_and_store_arguments(int argc, char* argv[], int* input_source) {
    /* Check input_source passed as argument (1 for CONSOLE_READ, 2 for FILE_READ)*/
    if(argc != 2) {
        printf("Input source not specified.\nPlease re-execute with input source as 1 for input through console and 2 for input through file.\n");
        return 0;
    }

    /* Convert from string to integer and store value of input source */
    *input_source = atoi(argv[1]);
    return 1;                       /* Successful */
}

int main(int argc, char* argv[]) {
    int             input_source = 0;               /* To record input source (to be taken from console or file) */
    char*           file_name = NULL;               /* To store file name */
    data_entry_t*   data_entry = NULL;              /* Data entry block to store the arrays and its sizes */
    int             index = 0;                      /* Loop iterator */

    if(!validate_and_store_arguments(argc, argv, &input_source))
        return -1;

    /* Allocate memory for data entry struct */
    data_entry = malloc(sizeof(data_entry_t));
    if(data_entry == NULL) {
        printf("Memory allocation for input entry structure failed.\n");
        return -1;
    }

    switch(input_source) {
        case CONSOLE_READ:
            /* Take input array size from user */
            printf("Please enter size of input array: ");
            scanf("%d", &(data_entry->input_array_size));

            /* Take elements sequence array size from user */
            printf("Please enter size of array that needs to be found as the subset of input array: ");
            scanf("%d", &(data_entry->elements_sequence_size));

            /* Allocate memory for input and elements sequence array */
            data_entry->input_array = malloc(sizeof(int) * (data_entry->input_array_size));
            data_entry->elements_sequence = malloc(sizeof(int) * (data_entry->elements_sequence_size));

            if(data_entry->input_array == NULL || data_entry->elements_sequence == NULL) {
                printf("Memory allocation for input arrays failed.\n");
                return -1;
            }

            /* Take input array elements from user */
            printf("Please enter %d elements of the input array: ", data_entry->input_array_size);
            for(index = 0; index < (data_entry->input_array_size); index++) {
                scanf("%d", &(data_entry->input_array[index]));
            }

            /* Take elements sequence array that needs to be found as the subset from the user */
            printf("Please enter %d elements of the elements sequence array: ", data_entry->elements_sequence_size);
            for(index = 0; index < (data_entry->elements_sequence_size); index++) {
                scanf("%d", &(data_entry->elements_sequence[index]));
            }

            /* Find smallest possible subset covering the given elements in sequence from input array */
            find_smallest_subset(data_entry);
            free(data_entry->input_array);
            free(data_entry->elements_sequence);
            break;
        case FILE_READ:
            /* Allocate memory to store file name.
               File name size restricted to a maximum of 512 characters. */
            file_name = malloc(sizeof(char) * MAX_FILE_NAME_SIZE);

            if(file_name == NULL) {
                printf("Memory allocation for array to store file name failed.\n");
                return -1;
            }
            printf("Please enter file name from where input needs to be read: ");
            /* To ensure that scanf reads no more than (MAX_FILE_NAME_SIZE - 1) characters.
               -1 since a string has to be null ('\0') terminated. */
            scanf("%s", file_name);

            if(!read_data_from_file(file_name, data_entry)) {
                printf("Error reading data from file.\n");
                return -1;
            }

            free(file_name);
            break;
        default:
            printf("Invalid input source specified.\n");
            break;
    }

    free(data_entry);
    return 0;
}
