#pragma once
#include <string>
#include <stack>

class MathExpression
{
	std::string infixExpression;
	std::string postfixExpression;

	const std::string openBrackets{ "([{" };
	const std::string closeBrackets{ ")]}" };
	const std::string brackets = openBrackets + closeBrackets;

	const std::string addOperators = "+-";
	const std::string multOperators = "*/";
	const std::string operators = addOperators + multOperators;

public:
	MathExpression(std::string infixExpression = "")
		: infixExpression{ infixExpression },
		postfixExpression{ "" }{ }

	std::string& InfixExpression();
	std::string PostfixExpression();

	int CheckBrackets();
	void CreatePostfix();
	double Calculate();
};

