#pragma once

//Warning no characters checks performs, all characters must be digit and the first char it could be plus or minus sign
double stringToDouble(std::string c_expression)
{
	double c_value = 0;
	int val = 1;
	size_t i;

	//calculate value from last char to second
	for (i = c_expression.length() - 1; i > 0; i--)
	{
		c_value += (c_expression[i] - '0') * val;
		val *= 10;
	}
	//check first character is sign or digit
	if (i == 0)//if i not zero mean expression is empty
	{
		if (c_expression[i] == '-')
			c_value *= -1;
		else if (c_expression[i] == '+');
		else
			c_value += (c_expression[i] - '0') * val;
	}
	return c_value;
}

bool isOperator(char& c)
{
	return c == '+' || c == '*' || c == '-' || c == '/';
}

bool isSign(char& c)
{
	return c == '+' || c == '-';
}

double performOpeation(double a, double b, char op)
{
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;//WARNNING : remember to manage divide by zero exception
	}
}
int operationPriority(char op)
{
	if (op == '+' || op == '-')
		return 0;
	if (op == '*' || op == '/')
		return 1;
}

