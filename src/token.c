#include <stdlib.h>

#include "../include/token.h"

Token* CreateToken(TokenType type, char* data, int position) {
    Token* result = (Token*) malloc(sizeof(Token));
    result->type = type;
    result->data = data;
	result->position = position;
    return result;
}