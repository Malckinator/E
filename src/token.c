#include <stdlib.h>

#include "../include/token.h"

Token* CreateToken(Token_Type type, char* data) {
    Token* result = (Token*) malloc(sizeof(Token));
    result->type = type;
    result->data = data;
    return result;
}