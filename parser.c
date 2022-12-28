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

// term -> factor ((+|-) factor)*
Expr *term(Scanner *scanner) {
  Expr *exp = factor(scanner);
  Token token;
  while(match(scanner, '+') || match(scanner, '-')) {
    char op = scanner->peek->lexeme[0];
    exp = newBinary(exp, factor(scanner), op, scanner->line);
  }
  return exp;
}

// factor -> primary ((*|/|%) primary)*
Expr *factor(Scanner *scanner) {
  Expr *exp = primary(scanner);
  Token token;
  while(match(scanner, '*') || match(scanner, '/') || match(scanner, '%')) {
    char op = scanner->peek->lexeme[0];
    exp = newBinary(exp, primary(scanner), op, scanner->line);
  }

  return exp;
}

// primary -> NUMBER
Expr *primary(Scanner *scanner) {
  // For now only numbers
  Token token = nextToken(scanner);
  Expr *exp = newNumberLiteral(&token);
  return exp;
}

Expr *newBinary(Expr *left, Expr *right, char op, int line) {
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

Expr *parse(Scanner *scanner) {
  Token token;
  Expr *exp;
  // TODO: pay attention to this when we have multi line statements.
  while(!atEnd(scanner)) {
    exp = term(scanner);
  }

  return exp;
}