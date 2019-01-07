 // ArithmeticExpression header file by MouhcineFD

#pragma once//Visual Studion define once style

#include <string>
#include <vector>
#include "CharStat.h"

//Define errors codes
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

	//To make shure there no instance for ArithmeticExpression with invalid expression by producing a throw
	void assertExpression();

	
	//*************** Static members and methods ***************\\

	//checkSyntaxe to check expression syntaxe with optional arguments for external use
	static bool checkSyntax(std::string expression, int& errorIndex = noErrorIndex, int& errorCode = noErrorCode);
	static std::string getCodeMsg(int errorCode);

	//Defaults Errors options
	static int noErrorIndex;
	static int noErrorCode;

	//Errors messages contents
	static const std::string OPEN_PAR_ERROR_MSG;
	static const std::string CLOSE_PAR_ERROR_MSG;
	static const std::string SYNTAX_ERROR_MSG;
	static const std::string NO_ERROR_MSG;


private:
	std::string c_expression;						//The valide expression
	long double value;
	std::vector<ArithmeticExpression> c_operands;
	std::vector<ArithmeticExpression> c_operators;


};

