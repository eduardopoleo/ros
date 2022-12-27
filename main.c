#include <stdio.h>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
  char *buffer = "5-3+6\0";
  Scanner scanner;
  initScanner(&scanner, buffer);
  Expr *exp = parse(&scanner);
  double result = interpret(exp);

  printf("result %f", result);
  return 0;
}