#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/token.h"

Token* MakeTokens(char* source) {
    for (int i = 0; source[i] != '\0'; i++) {
        char c = source[i];

        if (c == '\0') {
            return CreateToken(EOS, "");
        } else if (isdigit(c)) {
            // TODO: implemet numbers
        } else if (c == '+') {
            return CreateToken(ADD, "");
        } else if (c == '-') {
            return CreateToken(SUB, "");
        } else if (c == '*') {
            return CreateToken(MUL, "");
        } else if (c == '/') {
            return CreateToken(DIV, "");
        } else if (c == '(') {
            return CreateToken(LPAREN, "");
        } else if (c == ')') {
            return CreateToken(RPAREN, "");
        } else if (isspace(c)) {
            continue;
        } else {
            char msg[22];
            sprintf(msg, "Invalid character '%c'", c);
            return CreateToken(ERROR, msg);
        }
    }
}