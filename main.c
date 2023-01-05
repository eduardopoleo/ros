#include <stdio.h>
#include <stdlib.h>
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
  - [x] Comments
  - [x] Strings
  - [x] Multiple statements
  - Free ast
  Stage 2:
  - puts
  - boolean related binary operation
  - control flow (if, for, while)
  - variables 
  - functions
  - closures (blocks)
  Stage 3:
  - arrays
  - hashes
  - classes (optional)
*/
int main(int argc, char *argv[]) {
  char *buffer = readFile(argv[1]);
  Scanner scanner;
  initScanner(&scanner, buffer);
  ExprArray expArray = parse(&scanner);

  Result result;
  for (int i = 0; i < expArray.size; i++) {
    result = interpret(expArray.list[i]);
    printf("result %f\n", result.number);
  }

  Expr *exp;
  for (int i = 0; i < expArray.size; i++) {
    exp = expArray.list[i];
    freeExpression(exp);
  }
  free(expArray.list);
  free(buffer);

  return 0;
}