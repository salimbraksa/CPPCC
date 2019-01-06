/* This is another way to do it, also in C.
** It is easier to do in editors that do not automatically indent the second
** through last lines of the comment one space from the first.
** It is also used in Holub's book, in rule 31.
*/

#include "pch.h"
#include <iostream>
#include <string>
#include"ArithmeticExpression.h"

using namespace std;

int main()
{
	/*
	const int nbrTest = 4;
	Expression aritExp[nbrTest];
	aritExp[0].setExpression("3+(5+(4*3))-12");
	aritExp[1].setExpression("3+(5+(4+*3))-12");
	aritExp[2].setExpression("3+((5+(4*3))-12");
	aritExp[3].setExpression("3+(5+(4*3))-12)");

	cout << "Test 1 :\n";
	cout << aritExp[0];
	if (Expression::checkSyntax(aritExp[0]))
		std::cout << " : Error\n";
	else
		std::cout << " : Passed\n";

	cout << "Test 2 :\n";
	cout << aritExp[1];
	if (Expression::checkSyntax(aritExp[1], errorIndex))
	{
		cout << " : Error there ^\n";
		for (size_t i = 0; i < errorIndex; i++)
			cout << " ";
		std::cout << "^" << endl;
	}
	else
		std::cout << " : Passed\n";

	std::cout << "Test 3 :\n";
	std::cout << aritExp[2];
	if (Expression::checkSyntax(aritExp[2], errorIndex,errorCode))
	{
		std::cout << " : Error there ^\n";
		for (size_t i = 0; i < errorIndex; i++)
			std::cout << " ";
		std::cout << "^" << endl;
	}
	else
		std::cout << " : Passed\n";

	std::cout << "Test 4 :\n";
	std::cout << aritExp[3];
	if (Expression::checkSyntax(aritExp[3], errorIndex, errorCode))
	{
		std::cout << " : Error there ^\n";
		for (size_t i = 0; i < errorIndex; i++)
			std::cout << " ";
		std::cout << "^"<<endl;
	}
	else
		std::cout << " : Passed\n";
	*/

	ArithmeticExpression aritExp1("3+(5+(4*3))-12");
	ArithmeticExpression aritExp2("+3+(-5+(4*+3))-+12");
	ArithmeticExpression aritExp3("++3+(5+(4*3))-12");
	ArithmeticExpression aritExp4("1++3+(5+(4*3))-12");
	ArithmeticExpression aritExp5("3+((5+(4*3))-12");
	ArithmeticExpression aritExp6("3+(5+(4*3)))-12");
	ArithmeticExpression aritExp7("3+(5+(4*3))-)12");
	ArithmeticExpression aritExp8("3+(5g+(4*3))-12");
	ArithmeticExpression aritExp9("3)+(5+(4*3))-12");

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
