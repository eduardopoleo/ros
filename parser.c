#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"

Expr *newExpr(int line, ExprType type) {
  Expr *exp = malloc(sizeof(*exp));

  exp->line = line;
  exp->type = type;

  return exp;
}

Expr *term(Scanner *scanner) {
  Expr *exp = literal(scanner);
  Token op;
  exp = literal(scanner);
  while(match(scanner, PLUS)) {
    exp = newBinary(exp, literal(scanner), '+', scanner->line);
  }

  return exp;
}

Expr *literal(Scanner *scanner) {
  int length = (int)(scanner->lookahead - scanner->current);
  Expr *exp = newLiteral(scanner->current, length, scanner->line);
  return exp;
}

Expr *newBinary(Expr *left, Expr *right, char op, int line) {
  Expr *exp = newExpr(line, BINARY);
  exp->as.binary.left = left;
  exp->as.binary.right = right;
  exp->as.binary.op = op;

  return exp;
}

Expr *newLiteral(char *value, int length, int line) {
  Expr *exp = newExpr(line, LITERAL);
  exp->as.literal.value = value;
  exp->as.literal.length = length;
  return exp;
}

Expr *parse(Scanner *scanner) {
  Token token;
  Expr *exp;
  while(!atEnd(scanner)) {
    exp = term(scanner);
  }

  return exp;
}