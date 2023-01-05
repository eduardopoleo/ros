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
      int length;
    } stringLiteral;
  } as;
} Expr;

typedef struct ExprArray {
  Expr **list;
  int size;
  int capacity;
} ExprArray;

void initExpArray(ExprArray *array);
void writeExpArray(ExprArray *expArray, Expr *newExp);
int growExpCapacity(int capacity);
Expr **growExpArray(ExprArray *array, int newCapacity);

ExprArray parse(Scanner *scanner);
Expr *term(Scanner *scanner);
Expr *factor(Scanner *scanner);
Expr *primary(Scanner *scanner);
Expr *newExpr(int line, ExprType type);
Expr *newBinary(Expr *left, Expr *right, TokenType op, int line);
Expr *newNumberLiteral(Token *token);
Expr *newStringLiteral(Token *token);

#endif