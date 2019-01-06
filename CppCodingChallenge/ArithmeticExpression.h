 /* This is another way to do it, also in C.
 ** It is easier to do in editors that do not automatically indent the second
 ** through last lines of the comment one space from the first.
 ** It is also used in Holub's book, in rule 31.
 */
#pragma once

#include <string>
#include <vector>
#include "CharStat.h"

class ArithmeticExpression
{
public:
	ArithmeticExpression();
	ArithmeticExpression(std::string expression);
	~ArithmeticExpression();

	bool setExpression(std::string expression);

	int getIndexError() const { return c_indexError; }
	int getCodeError() const { return c_codeError; }
	std::string getCodeMsg();

	static std::string getCodeMsg(int errorCode);

	static int noErrorIndex;
	static int noErrorCode;
	static bool checkSyntax(std::string expression, int& errorIndex=noErrorIndex, int& errorCode= noErrorCode);
	static const std::string OPEN_PARENTHESES_FIRST;
	static const std::string CLOSE_PARENTHESES;
	static const std::string SYNTAXE_ERROR;


private:
	std::string c_expression;
	long double value;
	int c_indexError;
	int c_codeError;
	std::vector<ArithmeticExpression> c_operands;
	std::vector<ArithmeticExpression> c_operators;


};

