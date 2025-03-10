#include "MathExpression.h"

std::string& MathExpression::InfixExpression()
{
    return infixExpression;
}

std::string MathExpression::PostfixExpression()
{
    return postfixExpression;
}

int MathExpression::CheckBrackets()
{
    std::stack<char> stackBrackets;

    for (int position{}; position < infixExpression.length(); position++)
    {
        char symbol = infixExpression[position];
        
        if (brackets.find(symbol) == std::string::npos)
            continue;

        if (openBrackets.find(symbol) != std::string::npos)
            stackBrackets.push(symbol);

        if (closeBrackets.find(symbol) != std::string::npos)
        {
            if (stackBrackets.empty())
                return position;

            int typeCloseBracket = closeBrackets.find(symbol);
            int typeOpenBracket = openBrackets.find(stackBrackets.top());
            
            if (typeCloseBracket != typeOpenBracket)
                return position;

            stackBrackets.pop();
        }
    }
    if (!stackBrackets.empty())
        return infixExpression.length();

    return -1;
}

void MathExpression::CreatePostfix()
{
    std::stack<char> stackOperators;
    int position{};
    while (position < infixExpression.length())
    {
        char symbol = infixExpression[position];

        // space symbols
        if (isspace(symbol))
        {
            position++;
            continue;
        }
            

        // numbers
        if (isdigit(symbol) || symbol == '.')
        {
            std::string number{ "" };
            if (symbol == '.')
                number.push_back('0');

            while (position < infixExpression.length()
                && (isdigit(symbol) || 
                    symbol == '.' ||
                    tolower(symbol) == 'e'))
            {
                if (tolower(symbol) == 'e'
                    && infixExpression[position + 1] == '-')
                {
                    number.push_back(symbol);
                    number.push_back(infixExpression[position + 1]);
                    position++;
                }
                else
                    number.push_back(symbol);
                symbol = infixExpression[++position];
            }
            number.push_back('#');
            postfixExpression.append(number);
        }

        // open brackets
        if (openBrackets.find(symbol) != std::string::npos)
            stackOperators.push(symbol);

        // close brackets
        if (closeBrackets.find(symbol) != std::string::npos)
        {
            while (openBrackets.find(stackOperators.top()) == std::string::npos)
            {
                postfixExpression.push_back(stackOperators.top());
                stackOperators.pop();
            }
            stackOperators.pop();
        }

        position++;
    }
}
