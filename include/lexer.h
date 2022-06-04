#ifndef LEXER_H
#define LEXER_H

typedef enum TokenTypeEnum {
	EOS,
	ERROR,
	INT,
	FLOAT,
	ADD,
	SUB,
	MUL,
	DIV,
	LPAREN,
	RPAREN
} TokenType;

typedef struct TokenStruct {
	TokenType type;
	char* data;
	int position;
} Token;

Token* CreateToken(TokenType type, char* data, int position);
Token* MakeTokens(char* source);

#endif