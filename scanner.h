#ifndef scanner_h
#define scanner_h

#include <stdio.h>
#include "token.h"

typedef struct Scanner {
  char *current;
  char *lookahead;
  int line;
} Scanner;

void initScanner(Scanner *scanner, char *code);
Token nextToken(Scanner *scanner);

#endif