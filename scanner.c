#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "token.h"

void initScanner(Scanner *scanner, char *code) {
  scanner->start = code;
  scanner->current = code;
  scanner->line = 1;
}

Token newToken(TokenType type, int line, int length, char *lexeme) {
  Token token;
  token.type = type;
  token.line = line;
  token.length = length;
  token.lexeme = lexeme;

  return token;
}

Token nextToken(Scanner *scanner) {
  Token token = calculateToken(scanner);
  scanner->peek = &token;
  return token;
}

int atEnd(Scanner *scanner) {
  if (scanner->current[0] == EOF || scanner->current[0] == '\0') {
    return 1;
  }

  return 0;
}

Token calculateToken(Scanner *scanner) {
  scanner->start = scanner->current;
  advance(scanner);
  Token token;
  int length = (int)(scanner->current - scanner->start);
  printf("start %c\n", scanner->start[0]);
  switch (scanner->start[0]) {
    case '+':
      token = newToken(PLUS, scanner->line, 1, scanner->start);
      break;
    case '-':
      token = newToken(MINUS, scanner->line, 1, scanner->start);
      break;
    default:
      token = newToken(NUMBER, scanner->line, length, scanner->start);
      break;
  }
  return token;
}

int match(Scanner *scanner, char character) {
  if (scanner->current[0] == character) {
    Token token = calculateToken(scanner);
    scanner->peek = &token;
    return 1;
  }

  return 0;
}

void advance(Scanner *scanner) {
  scanner->current++;
}

void printCurrentChar(Scanner *scanner, char *message) {
  printf("%s: %c\n", message, scanner->start[0]);
}
