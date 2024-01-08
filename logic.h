#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

bool isOperator(char ch);
bool isLogicOperator(char ch);
int getPriority(char op);
double performOperation(char op, double operand1, double operand2);
string Infix2Postfix(const string& infix);
string Infix2Prefix(string infix);
string convertPrefixToPostfix(const string& prefix);
string removeTrailingZeros(const string& result);
string PostfixPrefixCalculator(const string& input);
int getPrecedence(char op);
int getPrecedence(string op);
bool isOperand(char ch);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
