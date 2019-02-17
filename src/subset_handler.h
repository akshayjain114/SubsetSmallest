#define MAX_FILE_NAME_SIZE 512
#define CONSOLE_READ 1
#define FILE_READ 2

typedef struct {
    int     input_array_size;            /* To store input array size */
    int     elements_sequence_size;      /* To store size of elements sequence array */
    int*    input_array;                 /* Input array tht will be checked for subsets */
    int*    elements_sequence;           /* Array that should be part of subset obtained from input array */
} data_entry_t;

extern void find_smallest_subset(data_entry_t* data_entry);

extern int read_data_from_file(char* file_name, data_entry_t* data_entry);

extern void print_data(data_entry_t* data_entry);
