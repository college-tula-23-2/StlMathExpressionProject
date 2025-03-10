// StlMathExpressionProject.cpp 
//
#include <iostream>
#include "MathExpression.h"

int main()
{
    MathExpression expr("(10.05 + {.20e2 - 4.0e-2} * 3)");

    std::cout << expr.CheckBrackets() << "\n";
    expr.CreatePostfix();
    std::cout << expr.PostfixExpression() << "\n";
}
