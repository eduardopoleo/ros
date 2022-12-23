#include <stdio.h>
#include "scanner.h"
#include "token.h"

int main(int argc, char *argv[]) {
  char *buffer = "6+5+4";
  Scanner scanner;
  initScanner(&scanner, buffer);
  return 0;
}