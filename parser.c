#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"

StmtArray parse(Scanner *scanner) {
  StmtArray stmtpArray;
  initStmtArray(&stmtpArray);

  Stmt *stmt;
  while(!atEnd(scanner)) {
    stmt = statement(scanner);
    writeStmtArray(&stmtpArray, stmt);
  }

  return stmtpArray;
}

Stmt *statement(Scanner *scanner) {
  if(match(scanner, PUTS)) {
    Expr *exp = expression(scanner);
    return newPuts(scanner->line, exp);
  } else {
    Stmt *stmt = newStmt(scanner->line, EXPR_STMT);
    stmt->exprStmt = expression(scanner);
    return stmt;
  }
}

Expr *expression(Scanner *scanner) {
  return term(scanner);
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

// Supporting functions: Should go into another file
Stmt *newPuts(int line, Expr *exp) {
  Stmt *stmt = newStmt(line, PUTS_STMT);
  stmt->as.puts.exp = exp;
  return stmt;
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

Stmt *newStmt(int line, StmtType type) {
  Stmt *stmt = (Stmt*)malloc(sizeof(*stmt));
  stmt->line = line;
  stmt->type = type;
  return stmt;
}

Expr *newExpr(int line, ExprType type) {
  Expr *exp = (Expr*)malloc(sizeof(*exp));

  exp->line = line;
  exp->type = type;

  return exp;
}

void freeStatements(StmtArray *array) {
  for(int i = 0; i < array->size; i++) {
    freeStatement(array->list[i]);
  }
}

void freeStatement(Stmt *stmt) {
  switch (stmt->type) {
    case PUTS_STMT:
      freeExpression(stmt->as.puts.exp);
      free(stmt);
      break;
    case EXPR_STMT:
      freeExpression(stmt->exprStmt);
      break;
  }
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

////////////// STMT ARRAY ////////////////////
void initStmtArray(StmtArray *array) {
  array->list = NULL;
  array->capacity = 0;
  array->size = 0;
}

void writeStmtArray(StmtArray *array, Stmt *stmt) {
  if (array->size + 1 > array->capacity) {
    int newCapacity = growStmtCapacity(array->capacity);
    array->list = growStmtArray(array, newCapacity);
  }

  array->list[array->size] = stmt;
  array->size++;
}

int growStmtCapacity(int capacity) {
  if (capacity < 8) {
    return 8;
  } else {
    return 2 * capacity;
  }
}

Stmt **growStmtArray(StmtArray *array, int newCapacity) {
  return (Stmt**)realloc(array->list, newCapacity * sizeof(Stmt));
}
//////////////////////////////////////////////
