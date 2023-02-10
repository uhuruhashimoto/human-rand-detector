#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
char **create_random_strings(int min_len, int max_len, int num_str);
void create_random_string(char *buff, int min_len, int max_len);
void zero_pad(char *buff, int len);
int write_to_txt_file(char **buff, int num_str, char *filename);

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
    int i = 0;
    // calculate string length
    RAND_bytes((unsigned char *)&i, sizeof(int));
    if (i < 0) {
        i = -i;
    }
    i = i % (max_len - min_len) + min_len;
    // generate rand bytes with OpenSSL of that length
    // each char is 8 bits
    int len_div_8 = i / 8;
    int num_chars = len_div_8 + 1;
    char *str = malloc(num_chars * sizeof(unsigned char));
    RAND_bytes((unsigned char*)str, num_chars);
    // convert bytes to string by bit shifting
    for (int j = 0; j < i; j++) {
        int byte_index = j / 8;
        int bit_index = j % 8;
        if ((str[byte_index] >> bit_index) & 1) {
            buff[j] = '1';
        } else {
            buff[j] = '0';
        }
    }
    zero_pad(buff, max_len);
}

/*
* Zero-pads all strings
*/
void zero_pad(char *buff, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        if (buff[i] == 0x00) {
            buff[i] = '0';
        }
    }
    buff[len] = '\0';
}

/*
* Writes zero-padded strings to a file in csv format
*/
int write_to_txt_file(char **buff, int num_str, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    int i;
    for (i = 0; i < num_str; i++) {
        fprintf(f, "%s\n", buff[i]);
    }
    fclose(f);
    return 0;
}

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
        zero_pad(buff[i], max_len);
        #ifdef DEBUG
        int zeros = 0;
        int ones = 0;
        for (int j = 0; j < max_len; j++) {
            if (buff[i][j] == '0') {
                zeros++;
            } else {
                ones++;
            }
        }
        printf("String %d: %s  | ", i, buff[i]);
        printf("Zeros: %d, Ones: %d\n", zeros, ones);
        #endif
    }
    printf("Writing random strings strings to file %s...\n", filename);
    write_to_txt_file(buff, num_str, filename);

}
