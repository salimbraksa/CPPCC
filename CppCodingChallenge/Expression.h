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

	static bool checkSyntax(std::string expression, int* errorIndex=nullptr, int* errorCode=nullptr);
private:
	std::vector<Expression> c_operands;
	std::vector<Expression> c_operators;

};

