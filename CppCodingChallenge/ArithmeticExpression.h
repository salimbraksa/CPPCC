 /* This is another way to do it, also in C.
 ** It is easier to do in editors that do not automatically indent the second
 ** through last lines of the comment one space from the first.
 ** It is also used in Holub's book, in rule 31.
 */

#pragma once

#include <string>
#include <vector>
#include "CharStat.h"

#define NO_ERROR_CODE 0x00
#define SYNTAX_ERROR_CODE 0x01
#define OPEN_PAR_ERROR_CODE 0x02
#define CLOSE_PAR_ERROR_CODE 0x03

class ArithmeticExpression
{
public:
	ArithmeticExpression();
	ArithmeticExpression(std::string expression);
	~ArithmeticExpression();

	void setExpression(std::string expression);

	void assertExpression();

	static bool checkSyntax(std::string expression, int& errorIndex = noErrorIndex, int& errorCode = noErrorCode);
	static std::string getCodeMsg(int errorCode);
	static int noErrorIndex;
	static int noErrorCode;
	static const std::string OPEN_PAR_ERROR_MSG;
	static const std::string CLOSE_PAR_ERROR_MSG;
	static const std::string SYNTAX_ERROR_MSG;
	static const std::string NO_ERROR_MSG;


private:
	std::string c_expression;
	long double value;
	std::vector<ArithmeticExpression> c_operands;
	std::vector<ArithmeticExpression> c_operators;


};

