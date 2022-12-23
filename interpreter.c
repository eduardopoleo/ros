#include <stdio.h>
#include "interpreter.h"
#include "parser.h"
#include "stdlib.h"
#include "string.h"

double interpret(Expr *exp) {
  switch (exp->type) {
    case BINARY:
      return interpret(exp->as.binary.left) + interpret(exp->as.binary.right);
    case NUMBER_LITERAL:
      return visitNumberLiteral(exp);
  }
}

double visitNumberLiteral(Expr *exp) {
  return exp->as.numberLiteral.number;
}

double visitBinary(Expr *exp) {
  switch (exp->as.binary.op) {
    case '+':
      return interpret(exp->as.binary.left) + interpret(exp->as.binary.right);
  }
}