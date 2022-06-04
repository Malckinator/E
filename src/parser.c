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

Expression* ParseTerm(Token* tokens, int* position) {
	Token token = tokens[*position];

	if (token.type == ADD || token.type == SUB) {
		(*position)++;
		printf("%d\n", *position);
		Expression* term = ParseTerm(tokens, position);
		if (term->type == ErrorExpression)
			return term;
		return CreateExpression(UnaryExpression, term, (int) token.type, NULL, "");
	}

	if (token.type == INT || token.type == FLOAT) {
		(*position)++;
		return CreateExpression(NumberExpression, NULL, (int) token.type, NULL, token.data);
	} else if (token.type == LPAREN) {
		(*position)++;
		Expression* expression = ParseExpression(tokens, position);
		if (tokens[*position].type != RPAREN)
			return CreateExpression(ErrorExpression, NULL, token.position, NULL, "Expected right bracket.");
		(*position)++;
		return expression;
	} else {
		return CreateExpression(ErrorExpression, NULL, token.position, NULL, "Exprected integer, float, or left bracket.");
	}
}

Expression* ParseFactor(Token* tokens, int* position) {
	Expression* left = ParseTerm(tokens, position);
	if (left->type == ErrorExpression)
		return left;

	while (tokens[*position].type == MUL || tokens[*position].type == DIV) {
		char op = '\0';
		Expression* right;

		if (tokens[*position].type == MUL)
			op = '*';
		else if (tokens[*position].type == DIV)
			op = '/';
		(*position)++;

		right = ParseTerm(tokens, position);
		if (right->type == ErrorExpression)
			return right;
		left = CreateExpression(BinaryExpression, left, (int) op, right, "");
	}

	return left;
}

Expression* ParseExpression(Token* tokens, int* position) {
	Expression* left = ParseFactor(tokens, position);
	if (left->type == ErrorExpression)
		return left;

	while (tokens[*position].type == ADD || tokens[*position].type == SUB) {
		char op = '\0';
		Expression* right;

		if (tokens[*position].type == ADD)
			op = '+';
		else if (tokens[*position].type == SUB)
			op = '-';
		(*position)++;

		right = ParseFactor(tokens, position);
		if (right->type == ErrorExpression)
			return right;
		left = CreateExpression(BinaryExpression, left, (int) op, right, "");
	}

	return left;
}

Expression* Parse(Token* tokens) {
	int position = 0;
	return ParseExpression(tokens, &position);
}