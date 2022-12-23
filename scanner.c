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

Token peek(Scanner *scanner) {
  char current_char = scanner->current[0];
  int length = (int)(scanner->lookahead - scanner->current);
  Token token;
  if (current_char == '+') {
    token = newToken(PLUS, scanner->line, length, scanner->current);
  } else {
    token = newToken(NUMBER, scanner->line, length, scanner->current);
  }

  return token;
}

Token nextToken(Scanner *scanner) {
  Token token = peek(scanner);
  advance(scanner);
  return token;
}

int atEnd(Scanner *scanner) {
  if (scanner->current[0] == EOF || scanner->current[0] == '\0') {
    return 1;
  }

  return 0;
}

int match(Scanner *scanner, TokenType type) {
  Token token = peek(scanner);
  if (token.type == type) {
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
