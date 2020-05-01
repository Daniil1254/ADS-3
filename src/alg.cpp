#include <iostream>
#include "tstack.h"
#include <string>

// преобразование выражения в постфиксную форму
std::string infx2pstfx(std::string inf)
{
	std::string result;
	TStack<char> stack;
	for (auto &symbol : inf)
	{
		int priority2 = priority(symbol);

		if (priority2 == -1)
			result += symbol;
		else if (stack.get() < priority2 || priority2 == 0 || stack.isEmpty())
			stack.push(symbol);
		else if (symbol == ')')
		{
			char simbol2 = stack.get();
			while ( priority(simbol2) >= priority2)
			{
				result += simbol2;
				stack.pop();
				simbol2 = stack.get();
			}
			stack.pop();
		}
		else
		{
			char simbol2 = stack.get();
			while ( priority(simbol2) >= priority2)
			{
				result += simbol2;
				stack.pop();
				simbol2 = stack.get();
			}
			stack.push(symbol);
		}
	}

	while (!stack.isEmpty())
	{
		result += stack.get();
		stack.pop();
	}
	return result;
}

// вычисление выражения, записанного в постфиксной форме
int eval(std::string pst)
{
	TStack<int> stack;
	for (auto &symbol : pst)
	{
		if (priority(symbol) == -1)
		{
			char s[2];
			s[0] = symbol;
			s[1] = '\0';
			int r = atoi(s); //Преобразуем char в тип int
			stack.push(r);
		}
		else
		{
			int b = stack.get();
			stack.pop();
			int a = stack.get();
			stack.pop();
			stack.push(score(a, b, symbol));
		}
	}
	return stack.get();
}

int  priority(const char &symbol)
{
	std::pair<char, int> priority[6];
	priority[0].first = '('; 
	priority[1].first = ')'; 
	priority[2].first = '+'; 
	priority[3].first = '-'; 
	priority[4].first = '*'; 
	priority[5].first = '/'; 
	priority[0].second = 0;
	priority[1].second = 1;
	priority[2].second = 2;
	priority[3].second = 2;
	priority[4].second = 3;
	priority[5].second = 3;

	int priority2 = -1;

	for (int j = 0; j < 6; ++j)
	if (symbol == priority[j].first)
	{
		priority2 = priority[j].second;
		break;
	}
	return priority2;
}

int score(const int &a, const int &b, const char &symbol)
{
	int result = 0;
	switch (symbol)
	{
	case '+':result = a + b;
		break;
	case '-':result = a - b;
		break;
	case '*':result = a * b;
		break;
	case '/':result = a / b;
		break;
	default:
		break;
	}
	return result;
}
