#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/lexer.h"
#include "../include/parser.h"

void DisplayParserTree(Expression* tree) {
	if (tree->type == NumberExpression) {
		printf("%s", tree->value);
	} else if (tree->type == BinaryExpression) {
		printf("(");
		DisplayParserTree(tree->left);
		printf(" %c ", (char) tree->op);
		DisplayParserTree(tree->right);
		printf(")");
	}
}

int main() {
	printf("Lexer:\n");
	Token* tokens = MakeTokens("12 + 32 - 5");
	for (int i = 0; true; i++) {
		Token token = tokens[i];
		printf("%d: '%s' at %d\n", token.type, token.data, token.position);
		if (token.type == EOS || token.type == ERROR)
			break;
	}

	printf("\nParser:\n");
	Expression* parserTree = Parse(tokens);
	free(tokens);
	if (parserTree->type == ErrorExpression)
		printf("Error: %s\n", parserTree->value);
	DisplayParserTree(parserTree);
	printf("\n");

	return 0;
}