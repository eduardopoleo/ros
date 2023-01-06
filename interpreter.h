#ifndef interpreter_h
#define interpreter_h

#include "parser.h"

typedef enum ResultType {
  NUMBER_RESULT,
  STRING_RESULT
} ResultType;

typedef struct Result {
  ResultType type;
  union {
    struct {
      double value;
    } number;

    struct {
      int length;
      char *value;
    } string;
  } as;
} Result;

void interpret(StmtArray *array);
void execute(Stmt *stmt);
void visitPuts(Stmt *stmt);
Result evaluate(Expr *exp);
Result visitStringLiteral(Expr *exp);
Result visitNumberLiteral(Expr *exp);
Result visitBinary(Expr *exp);

#endif