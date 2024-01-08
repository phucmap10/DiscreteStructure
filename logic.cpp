#include "logic.h"


bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int getPriority(char op)
{
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else if (op == '(')
        return 0;
    return -1;
}

double performOperation(char op, double operand1, double operand2) {
    if (op == '+')
        return operand1 + operand2;
    else if (op == '-')
        return operand1 - operand2;
    else if (op == '*')
        return operand1 * operand2;
    else if (op == '/')
        return operand1 / operand2;
    else if (op == '^')
        return pow(operand1, operand2);
    else
        return 0.0;
}

string Infix2Postfix(const string& infix)
{
    string postfix;
    stack<char> stack;

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isdigit(ch) || isalpha(ch)) {
            while (isdigit(ch) || isalpha(ch)) {
                postfix += ch;
                i++;

                if (i < infix.length())
                    ch = infix[i];
                else
                    break;
            }

            postfix += ' ';
            i--;  
        } else if (isOperator(ch)) {
            while (!stack.empty() && getPriority(ch) <= getPriority(stack.top())) {
                postfix += stack.top();
                stack.pop();
                postfix += ' ';
            }
            stack.push(ch);
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
                postfix += ' ';
            }
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            }
        }
    }

    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
        postfix += ' ';
    }

    return postfix;
}

string Infix2Prefix(string infix)
{
    string prefix;
    stack<char> stack;

    string reversedInfix = infix;
    reverse(reversedInfix.begin(), reversedInfix.end());

    bool digitFlag = false;
    for (char input : reversedInfix) {
        if (isdigit(input))
        {
            if (digitFlag)
            {
                prefix += input;
            }
            else
            {
                prefix += ' ';
                prefix += input;
                digitFlag = true;
            }
        }
        else if (input == ')')
        {
            stack.push(input);
            digitFlag = false;
        }
        else if (input == '(')
        {
            while (!stack.empty() && stack.top() != ')')
            {
                prefix += ' ';
                prefix += stack.top();
                stack.pop();
            }
            stack.pop();
            digitFlag = false;
        }
        else if (isOperator(input))
        {
            while (!stack.empty() && getPriority(stack.top()) > getPriority(input))
            {
                prefix += ' ';
                prefix += stack.top();
                stack.pop();
            }
            stack.push(input);
            digitFlag = false;
        }
    }

    while (!stack.empty())
    {
        prefix += ' ';
        prefix += stack.top();
        stack.pop();
    }

    reverse(prefix.begin(), prefix.end());

    return prefix;
}

string convertPrefixToPostfix(const string& prefix) {
    stack<string> stack;

    stringstream ss(prefix);
    string token;
    while (ss >> token) {
        if (isOperator(token[0])) {
            string operand2 = stack.top();
            stack.pop();
            string operand1 = stack.top();
            stack.pop();

            string postfix = operand1 + " " + operand2 + " " + token;
            stack.push(postfix);
        } else {
            stack.push(token);
        }
    }

    return stack.top();
}

string removeTrailingZeros(const string& result) {
    string formattedResult = result;

    size_t decimalPos = formattedResult.find('.');
    if (decimalPos != string::npos) {
        
        size_t lastNonZero = formattedResult.find_last_not_of('0');
        if (lastNonZero != string::npos) {
            
            if (formattedResult[lastNonZero] == '.') {
                lastNonZero--; 
            }
            formattedResult.erase(lastNonZero + 1, string::npos);
        }
    }

    return formattedResult;
}

string PostfixPrefixCalculator(const string& input) {
    if (isdigit(input[0])) {
        stack<double> stack;

        stringstream ss(input);
        string token;
        while (ss >> token) {
            if (isdigit(token[0])) {
                stack.push(stod(token));
            } else if (isOperator(token[0])) {
                double operand2 = stack.top();
                stack.pop();
                double operand1 = stack.top();
                stack.pop();

                double result = performOperation(token[0], operand1, operand2);
                stack.push(result);
            }
        }

        double finalResult = stack.top();
        double roundedResult;
        if (floor(finalResult) == finalResult) {
            roundedResult = finalResult;
        } else {
            roundedResult = round(finalResult * 10000) / 10000;
        }

        string formattedResult;
    if (std::fmod(roundedResult, 1.0) != 0.0) {
        formattedResult = to_string(roundedResult);
        size_t decimalPos = formattedResult.find('.');
        if (decimalPos != string::npos && decimalPos + 5 < formattedResult.size()) {
            formattedResult = formattedResult.substr(0, decimalPos + 5);
        }
    } else {
        formattedResult = to_string(static_cast<double>(roundedResult));
    }

    formattedResult = removeTrailingZeros(formattedResult);

    return formattedResult;
    } else {
        stack<double> stack;

        int length = input.length();
        for (int i = length - 1; i >= 0; --i) {
            char ch = input[i];

            if (isdigit(ch)) {
                string operand;
                while (i >= 0 && isdigit(input[i])) {
                    operand = input[i] + operand;
                    --i;
                }
                ++i;
                stack.push(stod(operand));
            } else if (isOperator(ch)) {
                double operand1 = stack.top();
                stack.pop();
                double operand2 = stack.top();
                stack.pop();

                double result = performOperation(ch, operand1, operand2);
                stack.push(result);
            }
        }

        double finalResult = stack.top();
        double roundedResult;
        if (floor(finalResult) == finalResult) {
            roundedResult = finalResult;
        } else {
            roundedResult = round(finalResult * 10000) / 10000;
        }

        string formattedResult;
    if (std::fmod(roundedResult, 1.0) != 0.0) {
        formattedResult = to_string(roundedResult);
        size_t decimalPos = formattedResult.find('.');
        if (decimalPos != string::npos && decimalPos + 5 < formattedResult.size()) {
            formattedResult = formattedResult.substr(0, decimalPos + 5);
        }
    } else {
        formattedResult = to_string(static_cast<double>(roundedResult));
    }

    formattedResult = removeTrailingZeros(formattedResult);

    return formattedResult;
    }
}

int getPrecedence(char op)
{
    if (op == '~')
        return 4;
    else if (op == '&' || op == '|')
        return 3;
    else if (op == '-')
        return 2;
    else if (op == '<')
        return 1;
    else
        return 0;
}

bool isLogicOperator(char c) {
    return (c == '&' || c == '|' || c == '~' || c == '-' || c == '<' || c == '>');
}

bool isOperand(char ch)
{
    return isalnum(ch);
}
int getPrecedence(string op)
{
    if (op == "~")
        return 4;
    else if (op == "&" || op == "|")
        return 3;
    else if (op == "->")
        return 2;
    else if (op == "<->")
        return 1;
    else
        return 0;
}

string LogicInfix2Postfix(string infix)
{
    string postfix = "";
    stack<string> operators;
    for (unsigned int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if (c == ' ')
            continue;
        if (isalpha(c))
        {
            postfix += c;
        }
        else if (c == '(')
        {
            operators.push(string(1, c));
        }
        else if (c == ')')
        {
            while (!operators.empty() && operators.top() != "(")
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            string op(1, c);
            if (c == '-' || c == '<')
            {
                op += infix[++i];
                if (c == '<')
                    op += infix[++i];
            }
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(op))
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(op);
        }
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}

string LogicInfix2Prefix(string infix)
{
    string prefix = "";
    stack<string> operators;
    for (int i = infix.length() - 1; i >= 0; i--)
    {
        char c = infix[i];
        if (c == ' ')
            continue;
        if (isalpha(c))
        {
            string variable(1, c);
            if (i > 0 && (infix[i - 1] == '-' || infix[i - 1] == '<'))
            {
                variable = infix[i - 1] + variable; 
                i--;
            }
            prefix = variable + prefix;
        }
        else if (c == ')')
        {
            operators.push(string(1, c));
        }
        else if (c == '(')
        {
            while (!operators.empty() && operators.top() != ")")
            {
                prefix = operators.top() + prefix;
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            string op(1, c);
            if (op == ">")
            {
                op = infix[--i] + op; // Append the previous character
                if (infix[--i] == '<')
                    op = "<" + op; // Prepend '<'
            }
            while (!operators.empty() && getPrecedence(operators.top()) > getPrecedence(op))
            {
                prefix = operators.top() + prefix;
                operators.pop();
            }
            operators.push(op);
        }
    }
    while (!operators.empty())
    {
        prefix = operators.top() + prefix;
        operators.pop();
    }
    return prefix;
}
