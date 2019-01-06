/* This is another way to do it, also in C.
** It is easier to do in editors that do not automatically indent the second
** through last lines of the comment one space from the first.
** It is also used in Holub's book, in rule 31.
*/

#include "pch.h"
#include <iostream>
#include <string>
#include"ArithmeticExpression.h"
#include"ArithmeticExpressionException.h"

using namespace std;

void printError(const ArithmeticExpressionException &e)
{
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
	cout << "ERROR : " << e.getExpression() << endl;
	cout << "Code : " << e.getCode() << endl;
	cout << "Message : " << e.what() << endl;
	cout << "Placement : ";
	cout << e.getExpression() << endl;
	cout << "            ";
	for (size_t i = 0; i < e.getIndex(); i++)
		cout << " ";
	cout << "^\n";
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

}

int main()
{
	try
	{
		ArithmeticExpression aritExp1("3+(5+(4*3))-12");
	}
	catch (const ArithmeticExpressionException& e)
	{
		printError(e);
	}
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

	cout << endl << "Hello mouhcine!" << endl;



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
