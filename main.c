#include <stdio.h>
#include "scanner.h"
#include "token.h"

int main(int argc, char *argv[]) {
  char *buffer = "6+5+4";
  Scanner scanner;
  initScanner(&scanner, buffer);
  Token token;
  token = nextToken(&scanner);
  printToken(&token);

  token = nextToken(&scanner);
  printToken(&token);

  token = nextToken(&scanner);
  printToken(&token);

  token = nextToken(&scanner);
  printToken(&token);

  token = nextToken(&scanner);
  printToken(&token);

  return 0;
}