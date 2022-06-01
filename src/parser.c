#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"

Expression* CreateExpression(ExpressionType type, Expression* left, int op, Expression* right, char* value) {
	Expression* result = (Expression*) malloc(sizeof(Expression));
	if (result == NULL) {
		printf("Failed to allocate memory\n");
		exit(0);
	}
	result->type = type;
	result->left = left;
	result->op = op;
	result->right = right;
	result->value = value;
	return result;
}

Token Peek(Token* tokens, int position) {
	int size;
	for (size = 0; tokens->type != EOS; size++) {}
	if (position >= size)
		return *CreateToken(EOS, "", 0);
	return tokens[position];
}

Expression* ParsePrimaryExpression(Token* tokens, int* position) {
	Token token = tokens[*position];
	if (!(token.type == INT || token.type == DOUBLE))
		return CreateExpression(ErrorExpression, NULL, token.position, NULL, "Unexpected token.");
	(*position)++;
	return CreateExpression(NumberExpression, NULL, 0, NULL, token.data);
}

Expression* Parse(Token* tokens) {
	int position = 0;
	Expression* left = ParsePrimaryExpression(tokens, &position);
	if (left->type == ErrorExpression)
		return left;

	while (tokens[position].type == ADD || tokens[position].type == SUB) {
		char op = '\0';
		Expression* right;

		if (tokens[position].type == ADD)
			op = '+';
		else if (tokens[position].type == SUB)
			op = '-';
		position++;

		right = ParsePrimaryExpression(tokens, &position);
		if (right->type == ErrorExpression)
			return right;
		left = CreateExpression(BinaryExpression, left, (int) op, right, "");
	}

	return left;
}