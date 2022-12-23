#ifndef scanner_h
#define scanner_h

#include <stdio.h>
#include "token.h"

typedef struct Scanner {
  char *current;
  char *lookahead;
  int line;
} Scanner;

void initScanner(Scanner *scanner, char *code);
Token newToken(TokenType type, int line, int length, char *lexeme);
Token nextToken(Scanner *scanner);
Token peek(Scanner *scanner);
int atEnd(Scanner *scanner);
int match(Scanner *scanner, TokenType type);
void advance(Scanner *scanner);
void printCurrentChar(Scanner *scanner, char *message);

#endif