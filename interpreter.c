#include <stdio.h>
#include "interpreter.h"
#include "token.h"
#include "parser.h"
#include "stdlib.h"
#include "string.h"

/*
  I need create a generic object model that can be returned from the 
  interpreter.The object model only gets translated into string when
  print for instance. Most likely we'll be using the same UNION approach
  from the expressions.
*/

Result interpret(Expr *exp) {
  switch (exp->type) {
    case BINARY:
      return visitBinary(exp);
    case NUMBER_LITERAL:
      return visitNumberLiteral(exp);
    case STRING_LITERAL:
      return visitStringLiteral(exp);
  }
}

Result visitStringLiteral(Expr *exp) {
  Result result;
  result.string = exp->as.stringLiteral.string;
  return result;
}

Result visitNumberLiteral(Expr *exp) {
  Result result;
  result.number = exp->as.numberLiteral.number;
  return result;
}

Result visitBinary(Expr *exp) {
  Result result;
  switch (exp->as.binary.op) {
    case PLUS:
      result.number = interpret(exp->as.binary.left).number + interpret(exp->as.binary.right).number;
      break;
    case MINUS:
      result.number = interpret(exp->as.binary.left).number - interpret(exp->as.binary.right).number;
      break;
    case STAR:
      result.number = interpret(exp->as.binary.left).number * interpret(exp->as.binary.right).number;
      break;
    case FORWARD_SLASH:
      result.number = interpret(exp->as.binary.left).number / interpret(exp->as.binary.right).number;
      break;
    case MODULO:
      result.number = (int)interpret(exp->as.binary.left).number % (int)interpret(exp->as.binary.right).number;
      break;
  }
  return result;
}