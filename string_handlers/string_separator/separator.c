#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv) {
    if (argc < 3) {
        printf("Usage: %s <filename> <separated filename>\n", argv[0]);
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    if (fp == NULL) {
        printf("Unable to open file %s\n", argv[1]);
        return -1;
    }
    char c;
    int count = 0;
    while((c = fgetc(fp)) != EOF) {
        if (count < 1000) {
            fprintf(fp2, "%c", c);
            count++;
        } else {
            fprintf(fp2, "\n%c", c);
            count = 1;
        }
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}
