#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void allocate_buffer(char **buff, int num_strings, int max_length);
int populate_buffer(char **buff, char *human_file, char *machine_file, int num_strings, int max_length);
int *shuffle_buffer(char **buff, int num_strings);
int write_to_csv_file(char **buff, int num_str, char *filename);
void write_ints_to_csv(int *arr, int num_ints, char *filename);

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <max_length> <num_strings_per_file> <human_file> <machine_file>\n", argv[0]);
        return -1;
    }
    int max_length = atoi(argv[1]);
    int num_strings = 2 * atoi(argv[2]);
    char *human_file = argv[3];
    char *machine_file = argv[4];
    
    // Create a buffer to hold the strings
    char **buff = malloc(num_strings * sizeof(char *));
    allocate_buffer(buff, num_strings, max_length);
    populate_buffer(buff, human_file, machine_file, num_strings, max_length);
    int *labels = shuffle_buffer(buff, num_strings);
    printf("Writing to file training.csv and labels.csv...\n");
    write_to_csv_file(buff, num_strings, "training.csv");
    write_ints_to_csv(labels, num_strings, "labels.csv");
    return 0;
    
}

void allocate_buffer(char **buff, int num_strings, int max_length)
{
    int i;
    for (i = 0; i < num_strings; i++) {
        buff[i] = malloc(max_length * sizeof(char));
        if (buff[i] == NULL) {
            printf("Error allocating memory\n");
        }
    }
}

int populate_buffer(char **buff, char *human_file, char *machine_file, int num_strings, int max_length)
{
    // open first file and populate the first half of the buffer
    FILE *f = fopen(human_file, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    for (int i= 0; i < num_strings/2; i++) {
        fgets(buff[i], max_length+1, f);
        // pad with zeros
        int len_str = strlen(buff[i]);
        for (int j = len_str-1; j < max_length; j++) {
            buff[i][j] = '0';
        }
        //buff[i][strlen(buff[i])-1] = 0x00;
    }
    fclose(f);
    FILE *f2 = fopen(machine_file, "r");
    if (f2 == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    char *temp = malloc(max_length * sizeof(char));
    for (int i = num_strings/2; i < num_strings; i++) {
        fgets(buff[i], max_length+1, f2);
        // clear buffer of single /0 character
        fgets(temp, max_length+1, f2);
        // buff[i][strlen(buff[i])-1] = 0x00;
    }
    free(temp);
    fclose(f2);
    return 0;
}

int *shuffle_buffer(char **buff, int num_strings)
{
    srand(time(NULL));
    int *labels = malloc(num_strings * sizeof(int));
    for (int i = 0; i < num_strings; i++) {
        if (i < num_strings/2) {
            // Human
            labels[i] = 1;
        } else {
            // Machine
            labels[i] = 0;
        }
    }
    for (int i = 0; i < num_strings; i++) {
        int j = rand() % num_strings;
        // swap strings
        char *temp = buff[i];
        buff[i] = buff[j];
        buff[j] = temp;
        // swap labels
        int temp2 = labels[i];
        labels[i] = labels[j];
        labels[j] = temp2;
    }
    return labels;
}

/*
* Writes zero-padded strings to a file in csv format
*/
int write_to_csv_file(char **buff, int num_str, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    int i;
    for (i = 0; i < num_str; i++) {
        fprintf(f, "%s", buff[i]);
        if (i < num_str-1) {
            fprintf(f, ",");
        }  

    }
    fclose(f);
    return 0;
}

void write_ints_to_csv(int *arr, int num_ints, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file\n");
    }
    int i;
    for (i = 0; i < num_ints; i++) {
        fprintf(f, "%d", arr[i]);
        if (i < num_ints-1) {
            fprintf(f, ",");
        }   
    }
    fclose(f);
}