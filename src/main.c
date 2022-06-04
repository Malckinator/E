#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/evaluator.h"

void DisplayParserTree(Expression* tree) {
	if (tree->type == NumberExpression) {
		printf("%s", tree->value);
	} else if (tree->type == UnaryExpression) {
		if (tree->op == ADD)
			printf("+");
		else if (tree->op == SUB)
			printf("-");

		DisplayParserTree(tree->left);
	} else if (tree->type == BinaryExpression) {
		printf("(");
		DisplayParserTree(tree->left);
		printf(" %c ", (char) tree->op);
		DisplayParserTree(tree->right);
		printf(")");
	}
}

int main() {
	Token* tokens = MakeTokens("-(2+5)");
	Expression* parserTree = Parse(tokens);
	int value = Evaluate(parserTree);

	printf("Lexer:\n");
	for (int i = 0; true; i++) {
		Token token = tokens[i];
		printf("%d: '%s' at %d\n", token.type, token.data, token.position);
		if (token.type == EOS || token.type == ERROR)
			break;
	}
	free(tokens);

	printf("\nParser:\n");
	if (parserTree->type == ErrorExpression)
		printf("Error: %s\n", parserTree->value);
	DisplayParserTree(parserTree);

	printf("\n\nValue: %d\n", value);

	return 0;
}