#ifndef token_h
#define token_h

#include <stdio.h>

typedef enum TokenType {
  PLUS, // 0
  MINUS, // 1
  NUMBER, // 2
  STAR, // 3
  FORWARD_SLASH, // 4
  MODULO, // 5
  END_OF_FILE // 6
} TokenType;

typedef struct Token {
  TokenType type;
  char *lexeme;
  int length;
  int line;
} Token;

void printToken(Token *token);

#endif