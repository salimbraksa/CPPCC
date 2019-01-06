#include "pch.h"
#include "ArithmeticExpression.h"
#include "ArithmeticExpressionException.h"

int ArithmeticExpression::noErrorIndex=-1;
int ArithmeticExpression::noErrorCode=NO_ERROR_CODE;

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
	assertExpression();
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

bool ArithmeticExpression::checkSyntax(std::string expression, int& errorIndex, int& errorCode)
{
	CharStat oldStat = EXP_BEGIN_CHAR;
	int nmbrOpenParentheses = 0;
	uint16_t i;
	int existErrorCode = NO_ERROR_CODE;
	for (i = 0; i < expression.length(); i++)
	{
		if ((expression[i] >= '0' && expression[i] <= '9') &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPERATOR_CHAR || oldStat == OPEN_PARENT_CHAR))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');
			i--;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') &&
			(oldStat == OPERAND_CHAR || oldStat == CLOSE_PARENT_CHAR))
		{
			oldStat = OPERATOR_CHAR;
		}
		else if (expression[i] == '(' &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPERATOR_CHAR || oldStat == OPEN_PARENT_CHAR))
		{
			oldStat = OPEN_PARENT_CHAR;
			nmbrOpenParentheses++;
		}
		else if (expression[i] == ')' &&
			(oldStat == OPERAND_CHAR || oldStat == CLOSE_PARENT_CHAR))
		{
			if (nmbrOpenParentheses == 0)
			{
				existErrorCode = CLOSE_PAR_ERROR_CODE;
				break;
			}
			oldStat = CLOSE_PARENT_CHAR;
			nmbrOpenParentheses--;
		}
		else if ((expression[i] == '+' || expression[i] == '-') &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPEN_PARENT_CHAR || oldStat == OPERATOR_CHAR) &&
			(++i < expression.length() && expression[i] >= '0' && expression[i] <= '9'))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');
			i--;
		}
		else
		{
			existErrorCode = SYNTAX_ERROR_CODE;
			break;
		}
	}

	if (existErrorCode == noErrorCode && nmbrOpenParentheses > 0)
	{
		existErrorCode = OPEN_PAR_ERROR_CODE;
		i--;
	}

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
