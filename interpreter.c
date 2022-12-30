#include <stdio.h>
#include "interpreter.h"
#include "token.h"
#include "parser.h"
#include "stdlib.h"
#include "string.h"

double interpret(Expr *exp) {
  switch (exp->type) {
    case BINARY:
      return visitBinary(exp);
    case NUMBER_LITERAL:
      return visitNumberLiteral(exp);
  }
}

double visitNumberLiteral(Expr *exp) {
  return exp->as.numberLiteral.number;
}

double visitBinary(Expr *exp) {
  switch (exp->as.binary.op) {
    case PLUS:
      return interpret(exp->as.binary.left) + interpret(exp->as.binary.right);
    case MINUS:
      return interpret(exp->as.binary.left) - interpret(exp->as.binary.right);
    case STAR:
      return interpret(exp->as.binary.left) * interpret(exp->as.binary.right);
    case FORWARD_SLASH:
      return interpret(exp->as.binary.left) / interpret(exp->as.binary.right);
    case MODULO:
      return (int)interpret(exp->as.binary.left) % (int)interpret(exp->as.binary.right);
  }
}