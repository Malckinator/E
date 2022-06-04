#ifndef PARSER_H
#define PARSER_H

#include "../include/lexer.h"

typedef enum ExpressionTypeEnum {
	ErrorExpression,
	NumberExpression,
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
Expression* ParseExpression(Token* tokens, int* position);
Expression* Parse(Token* tokens);

#endif