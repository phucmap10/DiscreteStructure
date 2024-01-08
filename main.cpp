#include "logic.h"

int main(){
	string infix = "251-451/213+542*242";
    string logicinfix = "~A&B|(C&D)^E&F";
    cout << "Infix to Postfix: " << Infix2Postfix(infix)<< endl;
    cout << "Infix to Prefix: " << Infix2Prefix(infix)<< endl;
    string kq1 = Infix2Postfix(infix);
    string kq2 = Infix2Prefix(infix);
    cout << "Prefix or Postfix Calculator: " << PostfixPrefixCalculator(kq1)<< endl;
    cout << "Prefix or Postfix Calculator: " << PostfixPrefixCalculator(kq2)<< endl;
    cout << "Infix to Postfix:(Logic): " << LogicInfix2Postfix(logicinfix)<< endl;
    cout << "Infix to Prefix:(Logic): " << LogicInfix2Prefix(logicinfix)<< endl;
}
