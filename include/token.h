#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_Type_Enum {
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
} Token_Type;

typedef struct Token_Struct {
    Token_Type type;
    char* data;
} Token;

Token* CreateToken(Token_Type type, char* data);

#endif