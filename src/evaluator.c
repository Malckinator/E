#include <stdlib.h>

#include "../include/evaluator.h"

int Evaluate(Expression* root) {
	return EvaluateExpression(root);
}

int EvaluateExpression(Expression* expression) {
	if (expression->type == NumberExpression) {
		return _atoi64(expression->value);
	} else if (expression->type == BinaryExpression) {
		int left = EvaluateExpression(expression->left);
		int right = EvaluateExpression(expression->right);

		if ((char) expression->op == '+') {
			return left + right;
		} else if ((char) expression->op == '-') {
			return left - right;
		} else if ((char) expression->op == '*') {
			return left * right;
		} else if ((char) expression->op == '/') {
			return left / right;
		}
	}
}