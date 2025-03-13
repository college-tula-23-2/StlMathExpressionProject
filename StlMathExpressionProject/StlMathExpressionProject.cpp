// StlMathExpressionProject.cpp 
//
#include <iostream>
#include "MathExpression.h"

int main()
{
    MathExpression expr("(-5 + 7) * -6");

    std::cout << expr.CheckBrackets() << "\n";
    expr.CreatePostfix();
    std::cout << expr.PostfixExpression() << "\n";
    std::cout << "Result = " << expr.Calculate() << "\n";
}
