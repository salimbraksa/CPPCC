 /* This is another way to do it, also in C.
 ** It is easier to do in editors that do not automatically indent the second
 ** through last lines of the comment one space from the first.
 ** It is also used in Holub's book, in rule 31.
 */
#pragma once

#include <string>
#include <vector>
#include "CharStat.h"

class Expression
{
public:
	Expression();
	Expression(std::string expression);
	~Expression();

	int getIndexError() const;
	int getCodeError() const;
	static int noErrorIndex;
	static int noErrorCode;
	static bool checkSyntax(std::string expression, int& errorIndex=noErrorIndex, int& errorCode= noErrorCode);

private:
	std::string c_expression;
	int c_indexError;
	int c_codeError;
	std::vector<Expression> c_operands;
	std::vector<Expression> c_operators;


};

