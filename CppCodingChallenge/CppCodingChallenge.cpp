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
		string str = "3+(5+(4*3))-12";//8
		ArithmeticExpression aritExp(str);

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
	*/



}