#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *ch_num = NULL;
  int ch_size = 0;
  int ch_allocation = 0;

  long cal_largest = 0;
  long cal_current = 0;

  char ch;
  char ch_prev;

  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    perror("Error opening the file");
    return -1;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      if (ch == ch_prev) {
        cal_largest = cal_current > cal_largest ? cal_current : cal_largest;

        cal_current = 0;
      } else {
        cal_current += atol(ch_num);
      }

      free(ch_num);
      ch_num = NULL;
      ch_size = 0;
      ch_allocation = 0;
    }

    ch_num = ch_num == NULL ? malloc(ch_allocation += 1)
                            : realloc(ch_num, ch_allocation += 1);
    ch_num[ch_size] = ch;
    ch_size++;

    ch_prev = ch;
  }

  cal_largest = cal_current > cal_largest ? cal_current : cal_largest;
  printf("%li\n", cal_largest);

  fclose(file);
  return 0;
}
