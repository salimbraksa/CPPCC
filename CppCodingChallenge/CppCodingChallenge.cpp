/*
** C++ Coding Challenge for United Remote
** The application of FAIRADI MOUHCINE (MouhcineFD)
** mail: mouhcinefd@outlook.com
** GSM : +212658406658
*/

#include <iostream>

#include <string>
#include "src/ArithmeticExpression.h"
#include "src/ArithmeticExpressionException.h"

using namespace std;

//Temporary UserOutput console error
void printError(const ArithmeticExpressionException &e)
{
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
	cout << "ERROR : " << e.getExpression() << endl;
	cout << "Code : " << e.getCode() << endl;
	cout << "Message : " << e.what() << endl;
	cout << "Placement : ";
	cout << e.getExpression() << endl;
	cout << "            ";
	for (int i = 0; i < e.getIndex(); i++)
		cout << " ";
	cout << "^\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

}

void sampleValidExp()
{
	string str;
	ArithmeticExpression aritExp;
	try
	{
		str = "3+(5+(4*3))-12";// 8 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "(5*6)-(40+(1))";// -11 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "(((3+6)*(2-4))+9)";// -9 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "(8*(9+9)*5-(3*6-(3*5+2)))";// 719 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "1+1*2";// 3 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "1*2+1";// 3 real value with calculator
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

		str = "";// must be 0
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
}

void sampleInvalidExp()
{
	try
	{
		ArithmeticExpression aritExp("+3+(-5+(4*+3))-+12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("++3+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("1++3+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("3+((5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("3+(5+(4*3)))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("3+(5+(4*3))-)12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("3+(5g+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	try
	{
		ArithmeticExpression aritExp("3)+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{

		printError(e);
	}
}

int main()
{
	string expresion;
	cout << "Enter an expression : ";
	cin >> expresion;

	try
	{
		ArithmeticExpression aritExp(expresion);
		cout << expresion << " = " << aritExp << endl;
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	
	//Decomment to see result for some valid expression
	//sampleValidExp();

	//Decomment to see result for some invalid expression
	//sampleInvalidExp();

	//we can check an expression if valid, without evaluate
	//we can use the optional arguments if we want know more about the error
	/*
	expresion = "3+(5+(4-*3))-12";
	if (ArithmeticExpression::checkSyntax(expresion))
		cout << expresion << " : check syntax failure" << endl;
	*/
}