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

void interpret(StmtArray *array) {
  for(int i = 0; i < array->size; i++) {
    array->list[i];
    execute(array->list[i]);
  }
}

void execute(Stmt *stmt) {
  switch (stmt->type) {
  case PUTS_STMT:
    visitPuts(stmt);
    break;
  case EXPR_STMT:
    evaluate(stmt->exprStmt);
    break;
  }
}

void visitPuts(Stmt *stmt) {
  Result result = evaluate(stmt->as.puts.exp);
  switch (result.type) {
  case NUMBER_RESULT:
    printf("%f\n", result.as.number.value);
    break;
  case STRING_RESULT:
    for(int i = 1; i < result.as.string.length - 1; i++) {
      printf("%c", result.as.string.value[i]);
    }
    printf("\n");
    break;
  }
}

Result evaluate(Expr *exp) {
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
  result.type = STRING_RESULT;
  result.as.string.value = exp->as.stringLiteral.string;
  result.as.string.length = exp->as.stringLiteral.length;
  return result;
}

Result visitNumberLiteral(Expr *exp) {
  Result result;
  result.type = NUMBER_RESULT;
  result.as.number.value = exp->as.numberLiteral.number;
  return result;
}

Result visitBinary(Expr *exp) {
  Result result;
  result.type = NUMBER_RESULT;
  switch (exp->as.binary.op) {
    case PLUS:
      result.as.number.value = evaluate(exp->as.binary.left).as.number.value + evaluate(exp->as.binary.right).as.number.value;
      break;
    case MINUS:
      result.as.number.value = evaluate(exp->as.binary.left).as.number.value - evaluate(exp->as.binary.right).as.number.value;
      break;
    case STAR:
      result.as.number.value = evaluate(exp->as.binary.left).as.number.value * evaluate(exp->as.binary.right).as.number.value;
      break;
    case FORWARD_SLASH:
      result.as.number.value = evaluate(exp->as.binary.left).as.number.value / evaluate(exp->as.binary.right).as.number.value;
      break;
    case MODULO:
      result.as.number.value = (int)evaluate(exp->as.binary.left).as.number.value % (int)evaluate(exp->as.binary.right).as.number.value;
      break;
  }
  return result;
}