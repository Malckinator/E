#include <stdio.h>
#include <stdbool.h>

#include "../include/lexer.h"

int main() {
	Token* tokens = MakeTokens("");

	for (int i = 0; true; i++) {
		Token token = tokens[i];
		printf("%d: '%s' at %d\n", token.type, token.data, token.position);
		if (token.type == EOS || token.type == ERROR)
			break;
	}

	return 0;
}