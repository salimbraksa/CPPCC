// ArithmeticExpression cpp file by MouhcineFD

#include "pch.h"//For visual Studion
#include "ArithmeticExpression.h"
#include "ArithmeticExpressionException.h"

int ArithmeticExpression::noErrorIndex=-1;				//default index for no error
int ArithmeticExpression::noErrorCode=NO_ERROR_CODE;	//default error code 

const std::string ArithmeticExpression::OPEN_PAR_ERROR_MSG = "Openned parentheses too much";
const std::string ArithmeticExpression::CLOSE_PAR_ERROR_MSG = "Clossed parentheses too much";
const std::string ArithmeticExpression::SYNTAX_ERROR_MSG = "Syntaxe error";
const std::string ArithmeticExpression::NO_ERROR_MSG = "";



ArithmeticExpression::ArithmeticExpression(std::string expression) :c_expression(expression)
{
	assertExpression();//check expression if not valid, if the case a throw will produce
	performExpressions();
	evaluate();
}

ArithmeticExpression::~ArithmeticExpression()
{
	for (ArithmeticExpression* x : c_operands)
		delete x;
}

void ArithmeticExpression::setExpression(std::string expression)
{
	c_expression = expression;
	assertExpression();
	performExpressions();
	evaluate();
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
	case OPEN_PAR_ERROR_CODE:
		return OPEN_PAR_ERROR_MSG;
	case CLOSE_PAR_ERROR_CODE:
		return CLOSE_PAR_ERROR_MSG;
	}
	return NO_ERROR_MSG;
}



bool isOperator(char& c)
{
	return c == '+' || c == '*' || c == '-' || c == '/';
}

bool isSign(char& c)
{
	return c == '+' || c == '-';
}


void ArithmeticExpression::performExpressions()
{
	//to devide the expression into sub expression each sub expression in new instance
	// perform only on valide expression
	
	/*
	** this function will look first if there a global parentheses for example :
	** (A+B) expression content globalas parentheses not as A+B
	** the (A+B) expression will look as that
	**		Expression : (A+B)
	**			Expression : A+B
	**				Expression : A
	**				Expression : B
	** and the A+B expression will look as that
	**			Expression : A+B
	**				Expression : A
	**				Expression : B
	**
	** then will look for operrand
	** then for operator
	*/

	int nmbrOpennedPar = 0;

	for (uint16_t i = 0, j = 0; i < c_expression.length(); i++)
	{
		if (c_expression[i] == '(')
		{
			//all content from openned parentheses to closed parentheses will put it in new expression as an operand

			j = i;

			nmbrOpennedPar++;

			while (nmbrOpennedPar)
			{
				//we are shure there is an closed parentheses because this expression is valide
				//so we dont need to check if j++ less thes length of expression 
				j++;
				if (c_expression[j] == ')')
					nmbrOpennedPar--;
				else if (c_expression[j] == '(')
					nmbrOpennedPar++;
			}

			if (i == 0 && j == c_expression.length() - 1)//case of global parenthes
			{
				c_operands.push_back(new ArithmeticExpression(c_expression.substr(1, j - 1)));//we push expression whitout parentheses
			}
			else
				c_operands.push_back(new ArithmeticExpression(c_expression.substr(i, j - i + 1)));//other case we push as normal operand

			i = j;
		}
		else if (isdigit(c_expression[i]) || ((isSign(c_expression[i]) && (i == 0 || isOperator(c_expression[i - 1])))))
		{// the case for normal operand or signed operand
			j = i;
			while (++j < c_expression.length() && isdigit(c_expression[j]));
			j--;
			if (i != 0 || j != c_expression.length() - 1)//to not push an other expression in case if we have only one operand
				c_operands.push_back(new ArithmeticExpression(c_expression.substr(i, j - i + 1)));
			i = j;
		}
		else
		{ //because we are shure that is a valid expression, the remaining case is an operator
			c_operators.push_back(c_expression[i]);
		}
	}

}

double stringToDouble(std::string c_expression)
{
	double c_value = 0;
	int val = 1;
	size_t i;
	for (i = c_expression.length() - 1; i > 0; i--)
	{
		c_value += (c_expression[i] - '0') * val;
		val *= 10;
	}
	if (i == 0)
	{
		if (c_expression[i] == '-')
			c_value *= -1;
		else if (c_expression[i] == '+');
		else
			c_value += (c_expression[i] - '0') * val;
	}
	return c_value;
}

double perfotmOpeation(double a, double b, char op)
{
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;//WARNNING : remember to manage divide by zero exception
	}
}

void ArithmeticExpression::evaluate()
{
	if (c_operands.empty())
		c_value = stringToDouble(c_expression);
	else if (c_operands.size() == 1)
		c_value = c_operands.front()->c_value;
	else if (c_operands.size() == 2)
		c_value = perfotmOpeation(c_operands[0]->c_value, c_operands[1]->c_value, c_operators.front());

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
		if (isdigit(expression[i]) &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPERATOR_CHAR || oldStat == OPEN_PARENT_CHAR))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && isdigit(expression[i]));//if next char is number also will passed
			i--;
		}
		/*
		* case if current char is an operator
		* old char must be an nummber or clossed parentheses
		*/
		else if (isOperator(expression[i]) &&
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
		else if (isSign(expression[i]) &&
			(oldStat == EXP_BEGIN_CHAR || oldStat == OPEN_PARENT_CHAR || oldStat == OPERATOR_CHAR) &&
			(++i < expression.length() && isdigit(expression[i])))
		{
			oldStat = OPERAND_CHAR;
			while (++i < expression.length() && isdigit(expression[i]));
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

std::ostream& operator<<(std::ostream& flux, ArithmeticExpression const& expression)
{
	flux << expression.value();
	return flux;
}