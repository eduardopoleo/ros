#include <stdio.h>
#include "scanner.h"

typedef enum ExprType {
  BINARY,
  LITERAL
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
      char *value;
      int length;
    } literal;
  } as;
} Expr;

Expr *parse(Scanner *scanner);
Expr *term(Scanner *scanner);
Expr *literal(Scanner *scanner);
Expr *newExpr(int line, ExprType type);
Expr *newBinary(Expr *left, Expr *right, char op, int line);
Expr *newLiteral(char *value, int length, int line);
