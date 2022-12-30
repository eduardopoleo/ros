#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "token.h"
#include <stdbool.h>

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

bool atEnd(Scanner *scanner) {
  if (scanner->current[0] == EOF || scanner->current[0] == '\0') {
    return true;
  }

  return false;
}

Token calculateToken(Scanner *scanner) {
  scanner->start = scanner->current;
  advance(scanner);
  while(scanner->start[0] == '\n') {
    printf("got here\n");
    scanner->line++;
    scanner->start = scanner->current;
    advance(scanner);
  }

  char startChar = scanner->start[0];

  printf("start %c\n", startChar);
  Token token;
  switch (startChar) {
    case '+':
      token = newToken(PLUS, scanner->line, 1, scanner->start);
      break;
    case '-':
      token = newToken(MINUS, scanner->line, 1, scanner->start);
      break;
    case '*':
      token = newToken(STAR, scanner->line, 1, scanner->start);
      break;
    case '/':
      token = newToken(FORWARD_SLASH, scanner->line, 1, scanner->start);
      break;
    case '%':
      token = newToken(MODULO, scanner->line, 1, scanner->start);
      break;
    case '\0':
      token = newToken(END_OF_FILE, scanner->line, 1, scanner->start);
      break;
  }

  if(isNumber(startChar)) {
    captureFullNumber(scanner);
  }

  int length = (int)(scanner->current - scanner->start);
  token = newToken(NUMBER, scanner->line, length, scanner->start);

  return token;
}

void captureFullNumber(Scanner *scanner) {
  // Current could be a . if we have 1 digit e.g 1.5
  while(isNumber(scanner->current[0]) || scanner->current[0] == '.') {
    advance(scanner);
    // If we land into a . we can to keep iterating to gather all the decimal points
    if(scanner->current[0] == '.') {
      advance(scanner);
    }
  }
}

bool isNumber(char c) {
  if(c >= '0' && c <= '9') {
    return true;
  }

  return false;
}

bool match(Scanner *scanner, char character) {
  if (scanner->current[0] == character) {
    Token token = calculateToken(scanner);
    scanner->peek = &token;
    return true;
  }

  return false;
}

void advance(Scanner *scanner) {
  scanner->current++;
}

void printCurrentChar(Scanner *scanner, char *message) {
  printf("%s: %c\n", message, scanner->start[0]);
}
