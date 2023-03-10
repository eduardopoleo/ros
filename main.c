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
  - [x] Free objects: ast, dynamic arrays
  Stage 2:
  - [x] puts
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
  // Prep
  char *buffer = readFile(argv[1]);
  Scanner scanner;

  // Interpret program
  initScanner(&scanner, buffer);
  StmtArray statements = parse(&scanner);
  interpret(&statements);

  // Free all objects
  freeStatements(&statements);
  free(statements.list);
  free(buffer);

  return 0;
}