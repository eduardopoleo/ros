#include <stdio.h>
#include "file.h"
/*
- process a file
*/

int main(int argc, char *argv[]) {
  char *file = readFile(argv[1]);
  char *fp = file;

  while(*fp != '\0') {
    printf("%c", *fp);
    fp++;
  }
}