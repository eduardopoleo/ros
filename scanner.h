#ifndef scanner_h
#define scanner_h

#include <stdio.h>
#include "token.h"
#include <stdbool.h>

typedef struct Scanner {
  char *start;
  char *current;
  Token peek;
  Token peek_prev;
  int line;
} Scanner;

void initScanner(Scanner *scanner, char *code);
Token newToken(TokenType type, int line, int length, char *lexeme);
Token initToken(Scanner *scanner);
bool isWhiteSpace(char c);
bool isNewLine(char c);
Token advanceToken(Scanner *scanner);
Token calculateToken(Scanner *scanner);
bool atEnd(Scanner *scanner);
bool match(Scanner *scanner, TokenType type);
bool isNumber(char c);
void captureFullNumber(Scanner *scanner);
void captureFullString(Scanner *scanner);
void printCurrentChar(Scanner *scanner, char *message);

#endif