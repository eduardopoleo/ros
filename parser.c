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
  printf("hello %c\n", scanner->peek->lexeme[0]);
  Expr *exp = primary(scanner);
  Token token;
  while(match(scanner, '+') || match(scanner, '-')) {
    char op = scanner->peek->lexeme[0];    
    exp = newBinary(exp, primary(scanner), op, scanner->line);
  }
  return exp;
}

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
  exp->as.numberLiteral.number = strtod(token->lexeme, NULL);
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