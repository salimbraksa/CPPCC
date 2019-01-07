// ArithmeticExpression cpp file by MouhcineFD

#include "pch.h"//For visual Studion
#include "ArithmeticExpression.h"
#include "ArithmeticExpressionException.h"

int ArithmeticExpression::noErrorIndex=-1;//no index for error
int ArithmeticExpression::noErrorCode=NO_ERROR_CODE;//default error code 

const std::string ArithmeticExpression::OPEN_PAR_ERROR_MSG = "Openned parentheses too much";
const std::string ArithmeticExpression::CLOSE_PAR_ERROR_MSG = "Clossed parentheses too much";
const std::string ArithmeticExpression::SYNTAX_ERROR_MSG = "Syntaxe error";
const std::string ArithmeticExpression::NO_ERROR_MSG = "";

ArithmeticExpression::ArithmeticExpression()
{
	assertExpression();
}


ArithmeticExpression::ArithmeticExpression(std::string expression):c_expression(expression)
{
	assertExpression();//check expression if not valid, if the case a throw will produce
}

ArithmeticExpression::~ArithmeticExpression()
{
	
}

void ArithmeticExpression::setExpression(std::string expression)
{
	c_expression = expression;
	assertExpression();
}

void ArithmeticExpression::assertExpression()
{
	int code, index;
	if(checkSyntax(c_expression,index, code))
		throw ArithmeticExpressionException(c_expression, code, index, getCodeMsg(code));
}

std::string ArithmeticExpression::getCodeMsg(int errorCode)
{
	switch (errorCode)
	{
	case SYNTAX_ERROR_CODE:
		return SYNTAX_ERROR_MSG;
		break;
	case OPEN_PAR_ERROR_CODE:
		return OPEN_PAR_ERROR_MSG;
		break;
	case CLOSE_PAR_ERROR_CODE:
		return CLOSE_PAR_ERROR_MSG;
		break;
	default:
		return NO_ERROR_MSG;
		break;
	}
}

//static member function to check a syntax of expression 
bool ArithmeticExpression::checkSyntax(std::string expression, int& errorIndex, int& errorCode)
{
	CharStat oldStat = EXP_BEGIN_CHAR;
	int nmbrOpenedParentheses = 0;
	uint16_t i;
	int existErrorCode = NO_ERROR_CODE;

	for (i = 0; i < expression.length(); i++)
	{
		/*
		* case if current char is an number
		* old char must be an operator or openned parentheses
		* or current char must be the first in expression
		*/
		if ((expression[i] >= '0' && expression[i] <= '9') &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPERATOR_CHAR || oldStat == OPEN_PARENT_CHAR))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');//if next char is number also will passed
			i--;
		}
		/*
		* case if current char is an operator
		* old char must be an nummber or clossed parentheses
		*/
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') &&
			(oldStat == OPERAND_CHAR || oldStat == CLOSE_PARENT_CHAR))
		{
			oldStat = OPERATOR_CHAR;
		}
		/*
		* case if current char is an (
		* the old char must be an operator or another (
		* or in the begin of expression
		*/
		else if (expression[i] == '(' &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPERATOR_CHAR || oldStat == OPEN_PARENT_CHAR))
		{
			oldStat = OPEN_PARENT_CHAR;
			nmbrOpenedParentheses++;
		}
		/*
		* case if current char is an )
		* the old char must be a number or another )
		*/
		else if (expression[i] == ')' &&
			(oldStat == OPERAND_CHAR || oldStat == CLOSE_PARENT_CHAR))
		{
			//if number oppened parrentheses equal zero that mean we closed an parrentheses whithout oppenned an clossed error existe
			if (nmbrOpenedParentheses == 0)
			{
				existErrorCode = CLOSE_PAR_ERROR_CODE;
				break;
			}
			oldStat = CLOSE_PARENT_CHAR;
			nmbrOpenedParentheses--;
		}
		/*
		* case for signed number
		* current char must be + or - sign
		* and the next char must be a number
		* thats mean an signed operand
		*/
		else if ((expression[i] == '+' || expression[i] == '-') &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPEN_PARENT_CHAR || oldStat == OPERATOR_CHAR) &&
			(++i < expression.length() && expression[i] >= '0' && expression[i] <= '9'))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');
			i--;
		}
		/*
		* if not all cases
		* a syntax error existe
		*/
		else
		{
			existErrorCode = SYNTAX_ERROR_CODE;
			break;
		}
	}

	//if no error existe and number of openned parentheses different zero that mean there a openned parentheses not colosed
	//an openned error existe in expression
	if (existErrorCode == noErrorCode && nmbrOpenedParentheses > 0)
	{
		existErrorCode = OPEN_PAR_ERROR_CODE;
		i--;//decrement index because the loop finished not breaked
	}

	//to check optionals argumments
	if (existErrorCode!=NO_ERROR_CODE)
	{
		if (errorCode != noErrorCode)
		{
			errorCode = existErrorCode;
			errorIndex = i;
			return true;
		}
		if (errorIndex != noErrorIndex)
			errorIndex = i;
		return true;
	}

	return false;
}
