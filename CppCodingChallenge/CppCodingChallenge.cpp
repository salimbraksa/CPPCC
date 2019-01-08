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
		int a();
		string str = "((1-4)+6)+6";
		//double dbl = -999999999;
		//string str = "3+(5+(4*3))-12";
		//string str = "+1+(+2+(3*+4)/5)*+6/-7";
		ArithmeticExpression aritExp1(str);
		cout << aritExp1 << endl;
		//cout << atof(str.c_str()) << endl;
		//ArithmeticExpression aritExp1;
		//arit = "6/76";
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


	cout << endl << "Hello mouhcine!" << endl;

}