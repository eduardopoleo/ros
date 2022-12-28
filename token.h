#ifndef token_h
#define token_h

#include <stdio.h>

typedef enum TokenType {
  PLUS,
  MINUS,
  NUMBER,
  STAR,
  FORWARD_SLASH,
  MODULO
} TokenType;

typedef struct Token {
  TokenType type;
  char *lexeme;
  int length;
  int line;
} Token;

void printToken(Token *token);

#endif