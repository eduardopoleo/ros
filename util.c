#include <stdio.h>

char *extractSubString(char *originalString, int length) {
  char newString[length - 1];
  memcpy(newString, originalString, length - 1);
  newString[length] = '\0';
}