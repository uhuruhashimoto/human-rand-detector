#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 8192

// sample code for 62/162 randomness analysis hw
// sws, feb 2023

void test_randomness(int *array, int len) {

  // array is a sequence len integers, each 0 or 1
  // test if it's random

}

int main(int argc, char **argv)
{

  int i = 0, j;
  int len;
  int *array;

  
  char *buff = malloc(MAX_LINE_LEN);
  if ( (!buff) || (argc < 2))
    return -1;
  FILE *f = fopen(argv[1], "r");
  while (fgets(buff, MAX_LINE_LEN, f)) {
    len = strlen(buff);
    
    if (len > MAX_LINE_LEN - 2)
      printf("Warning: MAX_LINE_LEN may be too short\n");
    
    if (len > 1) {
      len--; // remove the newline
      buff[len] = 0x00;
      printf("h%d len=%d\n", i, len);
      printf("String read: [%s]\n\n", buff);

      array = calloc(len, sizeof(int));  // so it's all zeros
      if (NULL == array) {
	printf("calloc failed\n");
	return -1;
      }
      for (j = 0; j < len; j++) {
	if ('1'==buff[j])
	  array[j] = 1;
      }

      test_randomness(array, len);
      free(array);
      
      i++;
    }
  }


  fclose(f);
  return 0;
}
