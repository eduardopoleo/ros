#include <stdio.h>
#include "scanner.h"
#include "token.h"

void initScanner(Scanner *scanner, char *code) {
  scanner->current = code;
  scanner->lookahead = code + 1 ;
  scanner->line = 1;
}

Token newToken(Scanner *scanner, TokenType type) {
  Token token;
  token.type = type;
  token.line = scanner->line;
  token.start = scanner->current;
  token.length = (int)(scanner->lookahead - scanner->current);

  return token;
}

Token nextToken(Scanner *scanner) {
  char current_char = scanner->current[0];
  Token token;
  if (current_char == '+') {
    token = newToken(scanner, PLUS);
  } else {
    token = newToken(scanner, NUMBER);
  }

  scanner->current++;
  scanner->lookahead++;
  // Move the pointer 1 place forward to get the next token
  return token;
}