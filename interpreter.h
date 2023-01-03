#ifndef interpreter_h
#define interpreter_h

#include "parser.h"

typedef union Result {
  double number;
  char *string;
} Result;

Result interpret(Expr *exp);
Result visitStringLiteral(Expr *exp);
Result visitNumberLiteral(Expr *exp);
Result visitBinary(Expr *exp);

#endif