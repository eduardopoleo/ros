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
  if (scanner->start[0] == EOF || scanner->start[0] == '\0') {
    return true;
  }

  return false;
}

Token calculateToken(Scanner *scanner) {
  // Handles white spaces, 
  while(isWhiteSpace(scanner->start[0])) {
    scanner->start++;
  }

  while(isNewLine(scanner->start[0])) {
    scanner->line++;
    scanner->start++;
  }

  // handles single line comments
  while(scanner->start[0] == '#') {
    while(scanner->start[0] != '\n' && !atEnd(scanner)) {
      scanner->start++;
    }
    scanner->line++;
  }

  scanner->current = scanner->start + 1;
  char startChar = scanner->start[0];
  Token token;
  printf("start %c\n", startChar);
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
    int length = (int)(scanner->current - scanner->start);
    token = newToken(NUMBER, scanner->line, length, scanner->start);
  }

  scanner->start = scanner->current;
  return token;
}

void captureFullNumber(Scanner *scanner) {
  // Current could be a . if we have 1 digit e.g 1.5
  while(isNumber(scanner->current[0]) || scanner->current[0] == '.') {
    scanner->current++;
    // If we land into a . we can to keep iterating to gather all the decimal points
    if(scanner->current[0] == '.') {
      scanner->current++;
    }
  }
}

bool isNewLine(char c) {
  if(c == '\n') {
    return true;
  }

  return false;
}

bool isWhiteSpace(char c) {
  if(c == ' ' || c == '\t' || c == '\r') {
    return true;
  }

  return false;
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

void printCurrentChar(Scanner *scanner, char *message) {
  printf("%s: %c\n", message, scanner->start[0]);
}
