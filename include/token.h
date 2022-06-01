#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenTypeEnum {
    EOS,
    ERROR,
    INT,
    DOUBLE,
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

#endif