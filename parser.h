#ifndef parser_h
#define parser_h

#include <stdio.h>
#include "scanner.h"
#include "token.h"

typedef enum ExprType {
  BINARY,
  NUMBER_LITERAL,
  STRING_LITERAL
} ExprType;

typedef struct Expr {
  ExprType type;
  int line;
  union {
    struct {
      struct Expr *left;
      struct Expr *right;
      TokenType op;
    } binary;

    struct {
      double number;
    } numberLiteral;

    struct {
      char *string;
    } stringLiteral;
  } as;
} Expr;

Expr *parse(Scanner *scanner);
Expr *term(Scanner *scanner);
Expr *factor(Scanner *scanner);
Expr *primary(Scanner *scanner);
Expr *newExpr(int line, ExprType type);
Expr *newBinary(Expr *left, Expr *right, TokenType op, int line);
Expr *newNumberLiteral(Token *token);

#endif