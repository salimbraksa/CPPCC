#include "pch.h"
#include "Expression.h"

int Expression::noErrorIndex=-1;
int Expression::noErrorCode=0x00;

Expression::Expression()
{
}


Expression::Expression(std::string expression)
{
	c_expression = expression;
	checkSyntax(c_expression, c_indexError, c_codeError);
}

Expression::~Expression()
{
}

int Expression::getIndexError() const
{
	return c_indexError;
}

int Expression::getCodeError() const
{
	return c_codeError;
}

bool Expression::checkSyntax(std::string expression, int& errorIndex, int& errorCode)
{
	CharStat oldStat = EXP_BEGIN;
	int numPar = 0;
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
			numPar++;
		}
		else if (expression[i] == ')' &&
			(oldStat == OPERAND || oldStat == CLOSE_PARENT))
		{
			if (numPar == 0)
			{
				exitErrorCode = 0x03;
				break;
			}
			oldStat = CLOSE_PARENT;
			numPar--;
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

	if (numPar > 0)
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
