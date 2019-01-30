// ArithmeticExpressionException file by MouhcineFD
// each exception content an invalid expression string
// and code number of error
// and the index of error in expression
// and description of error

#pragma once
#include<exception>
#include<string>
#include"ArithmeticExpression.h"

class ArithmeticExpressionException : public std::exception
{
public:
	ArithmeticExpressionException(std::string const& expression,int code, int index = ArithmeticExpression::noErrorIndex, std::string const& content = "") throw()
		:m_expression(expression),m_code(code), m_index(index), m_content(content)
	{}

	virtual const char* what() const throw()
	{
		return m_content.c_str();
	}

	std::string getExpression() const throw()
	{
		return m_expression;
	}
	int getCode() const throw()
	{
		return m_code;
	}
	int getIndex() const throw()
	{
		return m_index;
	}

	virtual ~ArithmeticExpressionException() throw()
	{}

private:
	std::string m_expression;
	int m_code;
	int m_index;
	std::string m_content;
};
