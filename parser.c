#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"

// Maybe this should be 
void initExpArray(ExprArray *array) {
  array->list = NULL;
  array->capacity = 0;
  array->size = 0;
}

void writeExpArray(ExprArray *expArray, Expr *newExp) {
  if (expArray->size + 1 > expArray->capacity) {
    int newCapacity = growExpCapacity(expArray->capacity);
    expArray->list = growExpArray(expArray, newCapacity);
  }

  expArray->list[expArray->size] = newExp;
  expArray->size++;
}

int growExpCapacity(int capacity) {
  if (capacity < 8) {
    return 8;
  } else {
    return 2 * capacity;
  }
}

Expr **growExpArray(ExprArray *array, int newCapacity) {
  return (Expr**)realloc(array->list, newCapacity * sizeof(Expr));
}

ExprArray parse(Scanner *scanner) {
  ExprArray expArray;
  initExpArray(&expArray);

  Expr *exp;
  while(!atEnd(scanner)) {
    exp = term(scanner);
    writeExpArray(&expArray, exp);
  }

  return expArray;
}

// term -> factor ((+|-) factor)*
Expr *term(Scanner *scanner) {
  Expr *exp = factor(scanner);
  while(match(scanner, PLUS) || match(scanner, MINUS)) {
    TokenType op = scanner->peek_prev.type;
    exp = newBinary(exp, factor(scanner), op, scanner->line);
  }
  return exp;
}

// factor -> primary ((*|/|%) primary)*
Expr *factor(Scanner *scanner) {
  Expr *exp = primary(scanner);
  while(match(scanner, STAR) || match(scanner, FORWARD_SLASH) || match(scanner, MODULO)) {
    TokenType op = scanner->peek_prev.type;
    exp = newBinary(exp, primary(scanner), op, scanner->line);
  }

  return exp;
}

// primary -> NUMBER
Expr *primary(Scanner *scanner) {
  Token token = advanceToken(scanner);
  Expr *exp;
  switch (token.type){
  case STRING:
    exp = newStringLiteral(&token);
    break;
  case NUMBER:
    exp = newNumberLiteral(&token);
    break;
  }
  return exp;
}

Expr *newExpr(int line, ExprType type) {
  Expr *exp = (Expr*)malloc(sizeof(*exp));

  exp->line = line;
  exp->type = type;

  return exp;
}

Expr *newBinary(Expr *left, Expr *right, TokenType op, int line) {
  Expr *exp = newExpr(line, BINARY);
  exp->as.binary.left = left;
  exp->as.binary.right = right;
  exp->as.binary.op = op;

  return exp;
}

Expr *newNumberLiteral(Token *token) {
  Expr *exp = newExpr(token->line, NUMBER_LITERAL);
  double number = strtod(token->lexeme, NULL);
  exp->as.numberLiteral.number = number;
  return exp;
}

Expr *newStringLiteral(Token *token) {
  Expr *exp = newExpr(token->line, STRING_LITERAL);
  exp->as.stringLiteral.string = token->lexeme;
  exp->as.stringLiteral.length = token->length;
  return exp;
}

void freeExpression(Expr *exp) {
  switch (exp->type) {
    case BINARY:
      freeExpression(exp->as.binary.left);
      freeExpression(exp->as.binary.right);
      break;
    case NUMBER_LITERAL:
      free(exp);
      break;
    case STRING_LITERAL:
      free(exp);
      break;
  }
}
