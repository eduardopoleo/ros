#include <stdio.h>
#include "token.h"

void printToken(Token *token) {
  printf("Type: %d, Line: %d, ", token->type, token->line);
  char *buffer;
  printf("Literal: %.*s\n", token->length, token->lexeme);
}