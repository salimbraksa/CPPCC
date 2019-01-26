/* 
** C++ Coding Challenge for United Remote
** The application of FAIRADI MOUHCINE (MouhcineFD)
** mail: mouhcinefd@outlook.com
** GSM : +212658406658
*/

#include "pch.h"//Visual studio file
#include <iostream>

#include <string>
#include "ArithmeticExpression.h"
#include "ArithmeticExpressionException.h"

using namespace std;

//Temporrary UserOutput console error
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

int main()
{
	
	try
	{
		string str;
		ArithmeticExpression aritExp;

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

		str = "";// muste be 0
		aritExp.setExpression(str);
		cout << str << " = " << aritExp << endl;

	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	/*
	try
	{
		ArithmeticExpression aritExp2("+3+(-5+(4*+3))-+12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp3("++3+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp4("1++3+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp5("3+((5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp6("3+(5+(4*3)))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp7("3+(5+(4*3))-)12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp8("3+(5g+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
	try
	{
		ArithmeticExpression aritExp9("3)+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{

		printError(e);
	}

	ArithmeticExpression aritExp10;
	try
	{
		aritExp10.setExpression("3+(5+(4-*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}

	if(ArithmeticExpression::checkSyntax("3+(5+(4-*3))-12"))
		cout << "3+(5+(4-*3))-12 : check syntaxe faillure"<< endl;
	


try
{
	string str;
	cin >> str;

	ArithmeticExpression aritExp;

	aritExp.setExpression(str);
	cout << str << " = " << aritExp << endl;

}
catch (const ArithmeticExpressionException& e)
{
	printError(e);
}
*/


}