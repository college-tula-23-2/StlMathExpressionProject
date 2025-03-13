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
    bool isUnare = true;

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
            isUnare = false;
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
        if (openBrackets.find(symbol) != std::string::npos) {
            isUnare = true;
            stackOperators.push(symbol);
        }
            

        // close brackets
        if (closeBrackets.find(symbol) != std::string::npos)
        {
            isUnare = false;
            while (openBrackets.find(stackOperators.top()) == std::string::npos)
            {
                postfixExpression.push_back(stackOperators.top());
                stackOperators.pop();
            }
            stackOperators.pop(); 
        }

        // multiplex operations
        if (multOperators.find(symbol) != std::string::npos)
        {
            isUnare = true;
            while (!stackOperators.empty()
                && multOperators.find(stackOperators.top()) != std::string::npos)
            {
                postfixExpression.push_back(stackOperators.top());
                stackOperators.pop();
            }
            stackOperators.push(symbol);
        }

        // additive operations
        if (addOperators.find(symbol) != std::string::npos)
        {
            if (symbol == '-' && isUnare)
            {
                postfixExpression.push_back('~');
                isUnare = false;
                position++;
                continue;
            }

            isUnare = true;
            while (!stackOperators.empty()
                && operators.find(stackOperators.top()) != std::string::npos)
            {
                postfixExpression.push_back(stackOperators.top());
                stackOperators.pop();
            }
            stackOperators.push(symbol);
        }
        position++;
    }

    while (!stackOperators.empty())
    {
        postfixExpression.push_back(stackOperators.top());
        stackOperators.pop();
    }
}

double MathExpression::Calculate()
{
    std::stack<double> stackOperands;

    for (int position{}; position < postfixExpression.length(); position++)
    {
        char symbol = postfixExpression[position];

        if (isdigit(symbol) || symbol == '~')
        {
            std::string operand = "";
            if (symbol == '~')
            {
                operand.push_back('-');
                symbol = postfixExpression[++position];
            }
                

            while (symbol != '#')
            {
                operand.push_back(symbol);
                symbol = postfixExpression[++position];
            }
            stackOperands.push(std::stod(operand));
            continue;
        }
        if (operators.find(symbol) != std::string::npos)
        {
            double result{};
            double rightOperand = stackOperands.top(); 
            stackOperands.pop();

            double leftOperand = stackOperands.top();
            stackOperands.pop();

            switch (symbol)
            {
            case '+': result = leftOperand + rightOperand; break;
            case '-': result = leftOperand - rightOperand; break;
            case '*': result = leftOperand * rightOperand; break;
            case '/': result = leftOperand / rightOperand; break;
            default:
                break;
            }

            stackOperands.push(result);
        }
    }
    return stackOperands.top();
}
