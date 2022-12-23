#ifndef parser_h
#define parser_h

#include <stdio.h>
#include "scanner.h"

typedef enum ExprType {
  BINARY,
  NUMBER_LITERAL
} ExprType;

typedef struct Expr {
  ExprType type;
  int line;
  union {
    struct {
      struct Expr *left;
      struct Expr *right;
      char op;
    } binary;

    struct {
      double number;
    } numberLiteral;
  } as;
} Expr;

Expr *parse(Scanner *scanner);
Expr *term(Scanner *scanner);
Expr *primary(Scanner *scanner);
Expr *newExpr(int line, ExprType type);
Expr *newBinary(Expr *left, Expr *right, char op, int line);
Expr *newNumberLiteral(Token *token);

#endif