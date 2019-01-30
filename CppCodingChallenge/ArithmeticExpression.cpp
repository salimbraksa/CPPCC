// ArithmeticExpression cpp file by MouhcineFD

#include "ArithmeticExpression.h"
#include "ArithmeticExpressionException.h"
#include "../lib/GeneralItem.h"

int ArithmeticExpression::noErrorIndex=-1;				//default index for no error
int ArithmeticExpression::noErrorCode=NO_ERROR_CODE;	//default error code 

const std::string ArithmeticExpression::OPEN_PAR_ERROR_MSG = "Opened parentheses too much";
const std::string ArithmeticExpression::CLOSE_PAR_ERROR_MSG = "Closed parentheses too much";
const std::string ArithmeticExpression::SYNTAX_ERROR_MSG = "Syntax error";
const std::string ArithmeticExpression::NO_ERROR_MSG = "";

ArithmeticExpression::ArithmeticExpression()
{
	c_expression = "0";
	assertExpression();//check syntax expression if valid, if is not the case a throw will produce
	performExpressions();//prepare expression to evaluation by make it as a tree
	evaluate();//the evaluate function start from the last level in the tree,it's look like a recursive function
	// for example these expression 1+2*(3+4)-5
	//***** 1+2*(3+4)+5 :
	//            |----> Operands :
	//            |            |------> 1
	//            |            |------> 2
	//            |            |------> (3+4) :
	//            |      	   |		     |------> 3+4 :
	//			  |			   |					   |----> Operands :
	//            |            |                       |           |------> 3
	//            |            |                       |           |------> 4
	//			  |			   |					   |----> Operator :
	//            |            |                                   |------> +
	//            |            |------> 5
	//            |----> Operator :
	//                        |------> +
	//                        |------> *
	//                        |------> -

	/* the evaluation function will execute in this order : 
	*
	* First :	 1		  --> 1
	* 2nd   :	 2		  --> 2
	* 3rd   :	 3		  --> 3
	* 4th   :	 4		  --> 4
	* 5th   :	 3+4	  --> 7
	* 6th   :	 (3+4)	  --> 7
	* 7th   :	 5		  --> 5
	* 8th   :	 1+2*7-5  --> 10
	*
	* the result is 10
	*/
}

ArithmeticExpression::ArithmeticExpression(std::string expression) :c_expression(expression.empty() ? "0" : expression)
{
	assertExpression();//check syntax expression if valid, if is not the case a throw will produce
	performExpressions();//prepare expression to evaluation by make it as a tree
	evaluate();
}

ArithmeticExpression::~ArithmeticExpression()
{
	for (ArithmeticExpression* x : c_operands)
		delete x;
}

void ArithmeticExpression::setExpression(std::string expression)
{
	c_value = 0;

	for (ArithmeticExpression* x : c_operands)
		delete x;
	c_operands.clear();

	c_operators.clear();

	c_expression = expression.empty() ? "0": expression;
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

void ArithmeticExpression::performExpressions()
{
	//to divide the expression into sub expression each sub expression in new instance of ArithmeticExpression
	//Warning performExpressions performed only on valid input expression
	
	/*
	** this function will look first if there a global parentheses for example :
	** (A+B) expression content globals parentheses not as A+B
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
	** then will look for operand
	** then for operator
	*/

	int nmbrOpennedPar = 0;

	for (uint16_t i = 0, j = 0; i < c_expression.length(); i++)
	{
		if (c_expression[i] == '(')
		{
			//all content from opened parentheses to closed parentheses will put it in new expression as an operand

			j = i;

			nmbrOpennedPar++;

			while (nmbrOpennedPar)
			{
				//we are sure there is an closed parentheses because this expression is valid
				//so we don't need to check if j++ less then length of expression 
				j++;
				if (c_expression[j] == ')')
					nmbrOpennedPar--;
				else if (c_expression[j] == '(')
					nmbrOpennedPar++;
			}

			if (i == 0 && j == c_expression.length() - 1)//case of global parentheses
			{
				c_operands.push_back(new ArithmeticExpression(c_expression.substr(1, j - 1)));//we push expression without parentheses
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
		{ //because we are sure that is a valid expression, the remaining case is an operator
			c_operators.push_back(c_expression[i]);
		}
	}

}

void ArithmeticExpression::evaluate()
{
	//first case : only root node in tree, there no operands only 
	//Expression Example : A , B, C
	// **** A :
	//the value of expression is the value in string no evaluation method needed
	if (c_operands.empty())
		c_value = stringToDouble(c_expression);
	//second case : tree with one node
	//Expression Example : (A) , (B+C)
	// **** (A) :
	//		 |----> A :
	//or
	// **** (B+C) :
	//		 |----> B+C :
	//				 |----> B :
	//				 |----> + :
	//				 |----> C :
	//value of expression is the value of child
	else if (c_operands.size() == 1)
		c_value = c_operands.front()->c_value;
	//third case : tow node or tow operand and one operator
	//here we need to perform the operation to get the result
	//Expression Example : B*C
	// **** (B*C) :
	//		 |----> B*C :
	//				 |----> B :
	//				 |----> * :
	//				 |----> C :
	else if (c_operands.size() == 2)
		c_value = performOpeation(c_operands[0]->c_value, c_operands[1]->c_value, c_operators.front());
	else
	{
		//the others cases when the expression content more than tow operand or more than one operation
		//to evaluate we need to perform first the operation who has the priority 
		//Expression Example : 1+2*3+4*5
		//we perform first 2*3 then 1+6, then 4*5 ,and 7+20

		size_t i = 0;
		double restValue=0;
		char restOperator=' ';

		//loop for all operators
		while (i  < c_operands.size())
		{
			//First will perform all operation if the current operator has a priority equal or great than the next operator
			//for example A*B*C+D+E*F+G will calculate A*B*C+D and exit the loop
			c_value = c_operands[i]->c_value;
			while (i + 1 < c_operators.size() && operationPriority(c_operators[i]) >= operationPriority(c_operators[i + 1]))
			{
				c_value = performOpeation(c_value, c_operands[i + 1]->c_value, c_operators[i]);
				i++;
			}
			//then check if we are come in the last operator
			if (i + 1 == c_operators.size())
			{
				//if the case we calculate last operation
				c_value = performOpeation(c_value, c_operands[i + 1]->c_value, c_operators[i]);
				//and the check if the are an operation in rest if the case we calculate also
				if (restOperator != ' ')
					c_value = performOpeation(restValue, c_value, restOperator);
				break;//then break the loop because we are calculated all operations
			}
			else//the case if the current operator has priority less then the next
			{
				if (restOperator != ' ')//we check first if the are already an rest operator, if the case will calculate
					c_value = performOpeation(restValue, c_value, restOperator);
				//then store current value and current operation for the next iteration
				restValue = c_value;
				restOperator = c_operators[i];
			}
			i++;
		}

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
		* old char must be an operator or opened parentheses
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
		* old char must be an number or closed parentheses
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
			//if number opened parentheses equal zero that mean we closed an parentheses without opened an closed error exist
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
		* a syntax error exist
		*/
		else
		{
			existErrorCode = SYNTAX_ERROR_CODE;
			break;
		}
	}

	//if no error exist and number of opened parentheses different zero that mean there a opened parentheses not closed
	//an opened error exist in expression
	if (existErrorCode == noErrorCode && nmbrOpenedParentheses > 0)
	{
		existErrorCode = OPEN_PAR_ERROR_CODE;
		i--;//decrement index because the loop finished not breaked
	}

	//to check optionals arguments
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