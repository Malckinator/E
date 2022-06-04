#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "../include/lexer.h"

Token* CreateToken(TokenType type, char* data, int position) {
	Token* result = (Token*)malloc(sizeof(Token));
if (result == NULL) {
		printf("Failed to allocate memory\n");
		exit(0);
	}
	result->type = type;
	result->data = data;
	result->position = position;
	return result;
}

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

Token* MakeNumber(char* source, int* i) {
	char* strnum = malloc(sizeof(char));
	int size = 1;
	bool isDouble = false;
	int start = *i;

	do {
		void* temp = realloc(strnum, sizeof(char) * (size + 1));
		if (temp == NULL) {
			printf("Could not allocate memory.");
			exit(0);
		}
		strnum = (char*) temp;
		strnum[size - 1] = source[*i];
		strnum[size] = '\0';
		size++;

		if (source[*i] == '.') {
			if (isDouble)
				return CreateToken(ERROR, "Double decimal points.", *i);
			isDouble = true;
		}
		(*i)++;
	} while (isdigit(source[*i]) || source[*i] == '.');
	(*i)--;

	if (isDouble) {
		return CreateToken(DOUBLE, strnum, start);
	} else {
		return CreateToken(INT, strnum, start);
	}
}

Token* MakeTokens(char* source) {
	Token* list = malloc(0);
	int size = 0;

    for (int i = 0; true; i++) {
        char c = source[i];

        if (c == '\0') {
			AddTokenToList(&list, CreateToken(EOS, "", i), &size);
			return list;
        } else if (isdigit(c)) {
			Token* result = MakeNumber(source, &i);

			if (result->type == ERROR)
				return result;
			AddTokenToList(&list, result, &size);
        } else if (c == '+') {
			AddTokenToList(&list, CreateToken(ADD, "", i), &size);
        } else if (c == '-') {
			AddTokenToList(&list, CreateToken(SUB, "", i), &size);
        } else if (c == '*') {
			AddTokenToList(&list, CreateToken(MUL, "", i), &size);
        } else if (c == '/') {
			AddTokenToList(&list, CreateToken(DIV, "", i), &size);
        } else if (c == '(') {
			AddTokenToList(&list, CreateToken(LPAREN, "", i), &size);
        } else if (c == ')') {
			AddTokenToList(&list, CreateToken(RPAREN, "", i), &size);
        } else if (!isspace(c)) {
			char msg[22];
			sprintf_s(msg, 22, "Invalid character '%c'", c);
			return CreateToken(ERROR, msg, i);
        }
    }
}