#ifndef interpreter_h
#define interpreter_h

#include "parser.h"

double interpret(Expr *exp);
double visitNumberLiteral(Expr *exp);
double visitBinary(Expr *exp);

#endif