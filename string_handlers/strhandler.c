#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>

/*
Creates OpenSSL random strings of length randomly between two values
*/
int main(int argc, char **argv)
{
    if (argc < 4) {
        printf("Usage: ./strhandler <min_len> <max_len> <num_str> <filename>\n");
        return -1;
    }
    int min_len = atoi(argv[1]);
    int max_len = atoi(argv[2]);
    int num_str = atoi(argv[3]);
    char *filename = argv[4];

    char **buff = create_random_strings(min_len, max_len, num_str);
    for (int i = 0; i < num_str; i++) {
        printf("String %d: %s\n", i, buff[i]);
        zero_pad(buff[i], max_len);
        printf("String %d: %s\n", i, buff[i]);
    }
    return write_to_csv_file(buff, num_str, filename);
}

/*
Generate cryptographically-secure random strings with OpenSSL within a given max and min length
*/
char **create_random_strings(int min_len, int max_len, int num_str)
{
    char **buff = malloc(num_str * sizeof(char *));
    int i;
    for (i = 0; i < num_str; i++) {
        buff[i] = malloc(max_len * sizeof(char));
        create_random_string(buff[i], min_len, max_len);
    }
    return buff;
}

void create_random_string(char *buff, int min_len, int max_len)
{
    int i;
    // calculate string length
    RAND_bytes(&i, sizeof(int)); 
    i = i % (max_len - min_len) + min_len;
    // generate rand bytes with OpenSSL of that length
    char *str = malloc(i * sizeof(char));
    RAND_bytes(str, i);
    // convert bytes to string
    for (int j = 0; j < i; j++) {
        if (str[j] == 0x00) {
            buff[j] = '0';
        } else {
            buff[j] = '1';
        }
    }
    zero_pad(buff, max_len);
}

/*
* Zero-pads all strings
*/
int zero_pad(char *buff, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        if (buff[i] == 0x00) {
            buff[i] = '0';
        }
    }
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
        write_str_to_csv_file(f, buff[i]);
    }
    fclose(f);
    return 0;
}

void write_str_to_csv_file(FILE *f, char *str)
{
    fprinf(f, "%s", str);
    fprintf(",");
}