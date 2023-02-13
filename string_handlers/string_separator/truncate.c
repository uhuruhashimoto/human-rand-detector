#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 8192

int main(const int argc, const char **argv) {
    if (argc < 3) {
        printf("Usage: %s <filename> <separated filename>\n", argv[0]);
        return -1;
    }
    // Take first 1000 chars, padding with zeros if necessary
    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    if (fp == NULL) {
        printf("Unable to open file %s\n", argv[1]);
        return -1;
    }
    if (fp2 == NULL) {
        printf("Unable to open file %s\n", argv[2]);
        return -1;
    }
    char truncated_line[1001];
    int len = 0;
    int i = 0;
    char *buff = malloc(MAX_LINE_LEN);
    while (fgets(buff, MAX_LINE_LEN, fp)) {
        len = strlen(buff);
        if (len > 1) {
            len--; // remove the newline
            buff[len] = 0x00;
            printf("h%d len=%d\n", i, len);
            printf("String read: [%s]\n\n", buff);

            for (int j = 0; j < 1000; j++) {
                if (j < len-1) {
                    truncated_line[j] = buff[j];
                } else {
                    truncated_line[j] = '0';
                }
            }
            truncated_line[1000] = 0x00;
            fprintf(fp2, "%s\n", truncated_line);
        }
        i++;
    }
    free(buff);
    fclose(fp);
    fclose(fp2);
    return 0;
}
