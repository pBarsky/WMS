#include "../include/conversions.h"

int stringToInt(const char *a) {
  int c, sign = 0, offset, n;
  if (a[0] == '-') {
    sign = -1;
  }
  if (sign == -1) {
    offset = 1;
  } else {
    offset = 0;
  }
  n = 0;
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
  if (sign == -1) {
    n = -n;
  }
  return n;
}

char *scanString() {
  int c; // because getchar() -> int
  int i = 0;
  char *string = malloc(sizeof(char));
  char *tmp = NULL;
  if (string != NULL) {
    string[0] = '\0';
  } else {
    perror("AN ERROR OCCURRED");
    exit(-1);
  }
  while ((c = getchar()) != '\n' && c != EOF) {
    tmp = realloc(string, (size_t)i + 2);
    if (tmp != NULL) {
      string = tmp;
    } else {
      perror("AN ERROR OCCURRED");
      exit(-1);
    }
    if (string != NULL) {
      string[i] = (char)c;
      string[i + 1] = '\0';
    } else {
      perror("AN ERROR OCCURRED");
      exit(-1);
    }
    i++;
  }
  return string;
}

int intLen(int num) { return (int)floor(log10(abs(num))) + 1; }

int scanInt() {
  int result, _getcharResult;
  while (!scanf_s(" %d", &result) || result < 1) {
    puts("please input a posivite number (>=1)");
    while ((getchar()) != '\n')
      ; // clear stdin buffer
  }
  _getcharResult = getchar();
  return result;
}

int hashPassword(const char *src) {
  int result = 0;
  int srcLen = strlen(src);
  int i;
  for (i = 0; i < srcLen; i++) {
    result += (int)src[i];
  }
  return result;
}