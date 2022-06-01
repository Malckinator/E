#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../include/token.h"

void AddTokenToList(Token** list, Token* object, int* size) {
	void* temp = realloc(*list, sizeof(Token) * (*size + 1));
	if (temp == NULL) {
		printf("Could not allocate memory.");
		exit(0);
	}
	*list = (Token*) temp;
	(*list)[*size] = *object;
	(*size)++;
}

Token* MakeTokens(char* source) {
	Token* list = malloc(0);
	int size = 0;

    for (int i = 0; true; i++) {
        char c = source[i];

        if (c == '\0') {
			AddTokenToList(&list, CreateToken(EOS, ""), &size);
			return list;
        } else if (isdigit(c)) {
            // TODO: implemet numbers
        } else if (c == '+') {
			AddTokenToList(&list, CreateToken(ADD, ""), &size);
        } else if (c == '-') {
			AddTokenToList(&list, CreateToken(SUB, ""), &size);
        } else if (c == '*') {
			AddTokenToList(&list, CreateToken(MUL, ""), &size);
        } else if (c == '/') {
			AddTokenToList(&list, CreateToken(DIV, ""), &size);
        } else if (c == '(') {
			AddTokenToList(&list, CreateToken(LPAREN, ""), &size);
        } else if (c == ')') {
			AddTokenToList(&list, CreateToken(RPAREN, ""), &size);
        } else if (!isspace(c)) {
			char msg[22];
            sprintf_s(msg, 22, "Invalid character '%c'", c);
            return CreateToken(ERROR, msg);
        }
    }
}