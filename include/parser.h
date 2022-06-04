#ifndef PARSER_H
#define PARSER_H

#include "../include/lexer.h"

typedef enum ExpressionTypeEnum {
	ErrorExpression,
	NumberExpression,
	UnaryExpression,
	BinaryExpression
} ExpressionType;

typedef struct ExpressionStruct {
	ExpressionType type;
	struct ExpressionStruct* left;
	int op;
	struct ExpressionStruct* right;
	char* value;
} Expression;

Expression* CreateExpression(ExpressionType type, Expression* left, int op, Expression* right, char* value);
Token Peek(Token* tokens, int position);
Expression* ParseTerm(Token* tokens, int* position);
Expression* ParseFactor(Token* tokens, int* position);
Expression* ParseExpression(Token* tokens, int* position);
Expression* Parse(Token* tokens);

#endif