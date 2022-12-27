#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "token.h"

void initScanner(Scanner *scanner, char *code) {
  scanner->current = code;
  scanner->lookahead = code + 1 ;
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
  advance(scanner);
  return token;
}

int atEnd(Scanner *scanner) {
  if (scanner->current[0] == EOF || scanner->current[0] == '\0') {
    return 1;
  }

  return 0;
}

Token calculateToken(Scanner *scanner) {
  Token token;
  int length = (int)(scanner->lookahead - scanner->current);

  switch (scanner->current[0]) {
    case '+':
      token = newToken(PLUS, scanner->line, length, scanner->current);
      break;
    case '-':
      token = newToken(MINUS, scanner->line, length, scanner->current);
      break;
    default:
      token = newToken(NUMBER, scanner->line, length, scanner->current);
      break;
  }
  return token;
}

int match(Scanner *scanner, char character) {
  if (scanner->current[0] == character) {
    Token token = calculateToken(scanner);
    scanner->peek = &token;
    advance(scanner);
    return 1;
  }

  return 0;
}

void advance(Scanner *scanner) {
  scanner->current++;
  scanner->lookahead++;
}

void printCurrentChar(Scanner *scanner, char *message) {
  printf("%s: %c\n", message, scanner->current[0]);
}
