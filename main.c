#include <stdio.h>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"
#include "file.h"

/*
  Feature list:
  Stage 1:
  - [x] Multi digit numbers
  - [x] Floating Point support
  - [x] Multiplication
  - [x] Division
  - [x] Module
  - [x] ReadFile
  - [x] Blank spaces
  - [x] Multi line statement
  - Comments
  - puts
  - Strings
  - Free ast
  Stage 2:
  - boolean related binary operation
  - control flow
  - variables 
  - functions
  - closures (blocks)
  Stage 3:
  - arrays
  - hashes
  - classes (optional)
*/
int main(int argc, char *argv[]) {
  // "8-3+71.8*5+14%5\0"
  char *buffer = readFile(argv[1]);
  Scanner scanner;
  initScanner(&scanner, buffer);
  Expr *exp = parse(&scanner);
  double result = interpret(exp);

  printf("result %f", result);
  return 0;
}