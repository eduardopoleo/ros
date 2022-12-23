#ifndef token_h
#define token_h

#include <stdio.h>

typedef enum TokenType {
  PLUS,
  NUMBER
} TokenType;

typedef struct Token {
  TokenType type;
  char *start;
  int length;
  int line;
} Token;

void printToken(Token *token);

#endif