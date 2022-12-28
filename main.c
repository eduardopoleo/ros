#include <stdio.h>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

/*
  Feature list:
  Stage 1:
  - [x] Multi digit numbers
  - Blank spaces
  - Comments
  - ReadFile
  - Multiplication
  - Division
  - Module
  - Free ast
  Stage 2:
  - variables 
  - functions
  - closures (blocks)
  Stage 3:
  - arrays
  - hashes
  - classes (optional)
*/
int main(int argc, char *argv[]) {
  char *buffer = "1000+5-160+432\0";
  Scanner scanner;
  initScanner(&scanner, buffer);
  Expr *exp = parse(&scanner);
  double result = interpret(exp);

  printf("result %f", result);
  return 0;
}