#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "token.h"
#include <stdbool.h>

void initScanner(Scanner *scanner, char *code) {
  scanner->start = code;
  scanner->current = code;
  scanner->line = 1;
  Token token = initToken(scanner);
  scanner->peek = token;
}

Token newToken(TokenType type, int line, int length, char *lexeme) {
  Token token;
  token.type = type;
  token.line = line;
  token.length = length;
  token.lexeme = lexeme;

  return token;
}

Token initToken(Scanner *scanner) {
  Token token = calculateToken(scanner);
  scanner->peek = token;
  return token;
}

// Advances the token but returns the previously current token
Token advanceToken(Scanner *scanner) {
  Token prev = scanner->peek;
  scanner->peek = calculateToken(scanner);
  scanner->peek_prev = prev;
  return prev;
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
    scanner->line++;
    scanner->start = scanner->current;
    advance(scanner);
  }

  char startChar = scanner->start[0];

  printf("start %c\n", startChar);
  switch (startChar) {
    case '+':
      return newToken(PLUS, scanner->line, 1, scanner->start);
    case '-':
      return newToken(MINUS, scanner->line, 1, scanner->start);
    case '*':
      return newToken(STAR, scanner->line, 1, scanner->start);
    case '/':
      return newToken(FORWARD_SLASH, scanner->line, 1, scanner->start);
    case '%':
      return newToken(MODULO, scanner->line, 1, scanner->start);
    case '\0':
      return newToken(END_OF_FILE, scanner->line, 1, scanner->start);
  }

  if(isNumber(startChar)) {
    captureFullNumber(scanner);
  }

  int length = (int)(scanner->current - scanner->start);
  Token token = newToken(NUMBER, scanner->line, length, scanner->start);

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

bool match(Scanner *scanner, TokenType type) {
  if (scanner->peek.type == type) {
    advanceToken(scanner);
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
