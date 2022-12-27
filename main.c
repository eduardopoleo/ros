#include <stdio.h>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

/*
  Feature list:
  Stage
  - Multi digit numbers
  - Space in numbers
  - Comments
  - Process file
  - Multiplication
  - Division
  - Module
  - variables 
*/
int main(int argc, char *argv[]) {
  char *buffer = "1+5-6+3-8-9+0-7+5-3+5\0";
  Scanner scanner;
  initScanner(&scanner, buffer);
  Expr *exp = parse(&scanner);
  double result = interpret(exp);

  printf("result %f", result);
  return 0;
}