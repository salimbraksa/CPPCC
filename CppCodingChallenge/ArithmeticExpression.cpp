#include "pch.h"
#include "ArithmeticExpression.h"

int ArithmeticExpression::noErrorIndex=-1;
int ArithmeticExpression::noErrorCode=0x00;

const std::string ArithmeticExpression::OPEN_PARENTHESES_FIRST = "There no open parentheses for this ^";
const std::string ArithmeticExpression::CLOSE_PARENTHESES = "You must close parentheses there ^";
const std::string ArithmeticExpression::SYNTAXE_ERROR = "Syntaxe error there ^";

ArithmeticExpression::ArithmeticExpression()
{

}


ArithmeticExpression::ArithmeticExpression(std::string expression):c_expression(expression)
{
	checkSyntax(c_expression, c_indexError, c_codeError);
}

ArithmeticExpression::~ArithmeticExpression()
{
	
}

bool ArithmeticExpression::setExpression(std::string expression)
{
	c_expression = expression;
	return checkSyntax(c_expression, c_indexError, c_codeError);
}


std::string ArithmeticExpression::getCodeMsg()
{
	switch (c_codeError)
	{
	case 0x01:
		return SYNTAXE_ERROR;
		break;
	case 0x02:
		return CLOSE_PARENTHESES;
		break;
	case 0x03:
		return OPEN_PARENTHESES_FIRST;
		break;
	default:
		return nullptr;
		break;
	}
}

std::string ArithmeticExpression::getCodeMsg(int errorCode)
{
	switch (errorCode)
	{
	case 0x01:
		return SYNTAXE_ERROR;
		break;
	case 0x02:
		return CLOSE_PARENTHESES;
		break;
	case 0x03:
		return OPEN_PARENTHESES_FIRST;
		break;
	default:
		return nullptr;
		break;
	}
}

bool ArithmeticExpression::checkSyntax(std::string expression, int& errorIndex, int& errorCode)
{
	CharStat oldStat = EXP_BEGIN;
	int nmbrOpenParentheses = 0;
	uint16_t i;
	int exitErrorCode = 0;
	for (i = 0; i < expression.length(); i++)
	{
		if ((expression[i] >= '0' && expression[i] <= '9') &&
			(oldStat == EXP_BEGIN || oldStat == OPERATOR || oldStat == OPEN_PARENT))
		{
			oldStat = OPERAND;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');
			i--;
		}
		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') &&
			(oldStat == OPERAND || oldStat == CLOSE_PARENT))
		{
			oldStat = OPERATOR;
		}
		else if (expression[i] == '(' &&
			(oldStat == EXP_BEGIN || oldStat == OPERATOR || oldStat == OPEN_PARENT))
		{
			oldStat = OPEN_PARENT;
			nmbrOpenParentheses++;
		}
		else if (expression[i] == ')' &&
			(oldStat == OPERAND || oldStat == CLOSE_PARENT))
		{
			if (nmbrOpenParentheses == 0)
			{
				exitErrorCode = 0x03;
				break;
			}
			oldStat = CLOSE_PARENT;
			nmbrOpenParentheses--;
		}
		else if ((expression[i] == '+' || expression[i] == '-') &&
			(oldStat == EXP_BEGIN || oldStat == OPEN_PARENT || oldStat == OPERATOR) &&
			(++i < expression.length() && expression[i] >= '0' && expression[i] <= '9'))
		{
			oldStat = OPERAND;
			while (++i < expression.length() && expression[i] >= '0' && expression[i] <= '9');
			i--;
		}
		else
		{
			exitErrorCode = 0x01;
			break;
		}
	}

	if (nmbrOpenParentheses > 0)
		exitErrorCode = 0x02;

	if (exitErrorCode)
	{
		if (errorIndex!=noErrorIndex)
		{
			if (exitErrorCode == 0x02)
				i--;
			errorIndex = i;
		}
		if (errorCode!=noErrorCode)
			errorCode = exitErrorCode;
		return true;
	}

	return false;
}
